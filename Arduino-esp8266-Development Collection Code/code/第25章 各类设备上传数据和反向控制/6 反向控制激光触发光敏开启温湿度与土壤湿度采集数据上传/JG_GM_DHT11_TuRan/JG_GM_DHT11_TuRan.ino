/************************************************************************************************
   基于ESPDuino开发板，应用于iot.doit.am物联网平台，集上传传感器数据到远端与远端反向控制终端的例程源码
   本例采用TCP协议，通过WiFi透传模式进行远端控制与传输
   时间：2016.09.10；
   传感器：   4激光  *5光敏  *30温湿度DHT11  土壤温湿度
   功能说明： 把模块放到大棚蔬菜里面的土壤表面，假设周围环境比较阴暗，可以远端控制平台反向控制激光
              模块发出光线照射到光敏传感器上，触发模块上的DHT11和土壤检测模块开始工作，两个传感器读
              取周围环境的参数后源源不断地发送到远端平台显示出来。
   硬件连接： 温湿度--D4  光敏--D5  激光--D12  土壤--A0
 ***********************************************************************************************/
#include <ESP8266WiFi.h>

#define u8 unsigned char
//IO方向设置
#define DHT11_IO_IN()  pinMode(4, INPUT)
#define DHT11_IO_OUT() pinMode(4, OUTPUT)
////IO操作函数
#define DHT11_DQ_OUT 4 //数据端口 4
#define DHT11_DQ_IN  4  //数据端口 4

//光敏
#define lightSens 5
//激光发射
#define laser 12
//土壤湿度
#define mol A0
int mo = 0;
int lightVal = 0;

//所连接的WiFi热点账密
const char* ssid     = "Doit";
const char* password = "doit3305";

//数据接收的网络平台
const char* host = "iot.doit.am";//物联网平台
//const char* host = "diot.doit.am";
const int httpPort = 8810;
//登录平台的 用户名 与 秘钥Key （随机数）
const char* streamId   = "lin";
const char* privateKey = "dee5d879314b54dca7813364ff94b79a";

char ser[64];//串口接收数据缓冲区
char str[512];//网页接收数据缓冲区
WiFiClient client;// 使用WiFi客户端类创建TCP连接
//反向控制：
unsigned long MS_TIMER = 0;
unsigned long lastMSTimer = 0;
String comdata = "";
char flag = false;

/*******************************DHT11协议****************************************/
u8 temperature;
u8 humidity;
u8 t = 0;
//复位DHT11
void DHT11_Rst(void)
{
  DHT11_IO_OUT();   //SET OUTPUT
  digitalWrite(DHT11_DQ_OUT, LOW);   //拉低DQ
  delay(20);     //拉低至少18ms
  digitalWrite(DHT11_DQ_OUT, HIGH);   //DQ=1
  delayMicroseconds(30);       //主机拉高20~40us
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
u8 DHT11_Check(void)
{
  u8 retry = 0;
  DHT11_IO_IN();//SET INPUT
  while (digitalRead(DHT11_DQ_IN) && retry < 100) //DHT11会拉低40~80us
  {
    retry++;
    delayMicroseconds(1);
  };
  if (retry >= 100)return 1;
  else retry = 0;
  while (!digitalRead(DHT11_DQ_IN) && retry < 100) //DHT11拉低后会再次拉高40~80us
  {
    retry++;
    delayMicroseconds(1);
  };
  if (retry >= 100)return 1;
  return 0;
}
//从DHT11读取一个位
//返回值：1/0
u8 DHT11_Read_Bit(void)
{
  u8 retry = 0;
  while (digitalRead(DHT11_DQ_IN) && retry < 100) //等待变为低电平
  {
    retry++;
    delayMicroseconds(1);
  }
  retry = 0;
  while (!digitalRead(DHT11_DQ_IN) && retry < 100) //等待变高电平
  {
    retry++;
    delayMicroseconds(1);
  }
  delayMicroseconds(40);//等待40us
  if (digitalRead(DHT11_DQ_IN))return 1;
  else return 0;
}
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte(void)
{
  u8 i, dat;
  dat = 0;
  for (i = 0; i < 8; i++)
  {
    dat <<= 1;
    dat |= DHT11_Read_Bit();
  }
  return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT11_Read_Data(u8 *temp, u8 *humi)
{
  u8 buf[5];
  u8 i;
  DHT11_Rst();
  if (DHT11_Check() == 0)
  {
    for (i = 0; i < 5; i++) //读取40位数据
    {
      buf[i] = DHT11_Read_Byte();
    }
    if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
    {
      *humi = buf[0];
      *temp = buf[2];
    }
  } else return 1;
  return 0;
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在
u8 DHT11_Init(void)
{
  pinMode(4, OUTPUT);
  DHT11_Rst();
  return DHT11_Check();
}
/********************************************************************/

//各种传感器的初始化
void sensor_init()
{
  //光敏
  pinMode(lightSens, INPUT);
  //激光
  pinMode(laser, OUTPUT);
  digitalWrite(laser, LOW);
}

void setup()
{
  Serial.begin(115200);
  sensor_init();
  MS_TIMER = millis();
  //DHT11
  delay(10);
  if (DHT11_Init()) //DHT11初始化
  {
    Serial.println("DHT11 Error");
    delay(200);
  }
  Serial.println("DHT11 OK");

  //  wifi_station_set_auto_connect(0);//关闭自动连接
  WiFi.disconnect();/////////////////
  // 首先，我们连接到WiFi网络
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(50);
  Serial.print("connecting to ");
  Serial.println(host);

  // 使用WiFi客户端类创建TCP连接
  //  WiFiClient client;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }
}
unsigned long lastTick = 0;
void loop()
{
  lightVal = digitalRead(lightSens);//光敏 0-有光 1 无光

  if (flag == false)
  {
    if (millis() - MS_TIMER > 5000)
    {
      MS_TIMER = millis();
    }
  }

  //读传感器并发送
  //5s读一次
  if (millis() - lastTick > 1000)
  {
    lastTick = millis();
    static bool first_flag = true;
    if (first_flag)
    {
      first_flag = false;
      sprintf(str, "cmd=subscribe&topic=lin\r\n");//注册用户名，以让后面的反向控制得以是实现
      client.print(str);
      return;
    }
    //读传感器并发送
    DHT11_Read_Data(&temperature, &humidity); //读DHT温湿度值
    //    lightVal = digitalRead(lightSens);//光敏 0-有光 1 无光
    mo = (analogRead(mol)) * 5;//土壤湿度
    mo = map(mo, 0, 1023 * 5, 100, 0);//转化为百分数
    if (lightVal == 0)
    {
      sprintf(ser, "DHTtemp: %d'C; DHThumi: %d%; Soilmois: %d%.", temperature, humidity, mo);
      Serial.println(ser);
      sprintf(str, "cmd=upload&device_name=arduino1&data=%d&device_name=arduino2&data=%d&device_name=arduino3&data=%d&uid=lin&key=%s\r\n", humidity, mo, temperature, privateKey);
      client.print(str);
    }
    else
    {
      Serial.println("Please open Sensor!");
      sprintf(str, "cmd=upload&device_name=arduino1&data=0&device_name=arduino2&data=0&device_name=arduino3&data=0&uid=lin&key=%s\r\n", privateKey);
      client.print(str);
    }
  }

  if (client.available())
  {
    //读并处理
    // R读取服务器的应答的所有行，并把它们打印到串口
    String recDataStr = client.readStringUntil('\n');
    Serial.println(recDataStr);
    //方向控制：注意LED灯是在设备arduino那里控制，蜂鸣器是在设备arduino1那里控制
    if (recDataStr.compareTo("cmd=publish&device_name=arduino&device_cmd=open\r") == 0)
    {
      digitalWrite(laser, HIGH);
      Serial.println("Open Sensor !");
    }
    else if (recDataStr.compareTo("cmd=publish&device_name=arduino&device_cmd=close\r") == 0)
    {
      digitalWrite(laser, LOW);
      Serial.println("Close Sensor !");
    }
  }
}



