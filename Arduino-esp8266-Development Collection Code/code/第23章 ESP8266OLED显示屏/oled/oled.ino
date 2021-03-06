#include <Wire.h>
#include "OLED.h"

static const char logo[] PROGMEM={
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0xff,0x03,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0x7f,0x00,0x00,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0x03,0x00,0x00,0x00,0xf8,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0x03,0x00,0xe0,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x1f,0x1c,0xf0,0x1f,0x00,0x80,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x0f,0x00,0x80,0x7f,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0xff,0x01,0x00,0xfc,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x07,0x00,0x00,0xfe,0x03,0x00,0xf8,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x03,0x00,0x00,0xfc,0x07,0x00,0xf8,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x01,0x00,0x00,0xf8,0x0f,0x00,0xf0,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x00,0x00,0x00,0xf0,0x1f,0x00,0xf0,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x3f,0x00,0x00,0x00,0xf0,0x1f,0x00,0xf0,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x1f,0x00,0x00,0x00,0xf0,0x1f,0x00,0xf0,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x1f,0x00,0x00,0x00,0xf0,0x1f,0x00,0xf0,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x0f,0x00,0x00,0x00,0xf0,0x3f,0x00,0xf0,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x07,0x00,0x00,0x00,0xf0,0x1f,0x00,0xf8,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x07,0x00,0x00,0x00,0xf0,0x0f,0x00,0xf8,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x03,0x00,0x00,0x00,0xf8,0x03,0x00,0xfc,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x01,0x00,0x00,0x00,0xfc,0x00,0x00,0x7e,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x01,0x00,0x00,0x00,0x7f,0x00,0x00,0x7f,0xf8,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x00,0x00,0x00,0x80,0x1f,0x00,0x80,0x7f,0xf8,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x00,0x00,0x00,0xe0,0x07,0x00,0xc0,0x3f,0xf0,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x00,0x00,0x00,0xf8,0x01,0x00,0xe0,0x3f,0xf0,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0x00,0x00,0x7f,0x00,0x00,0xf8,0x3f,0xf0,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0x00,0xe0,0x1f,0x00,0x00,0xfe,0x0f,0xf0,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0x00,0xf8,0x03,0x00,0x80,0xff,0x0f,0xf8,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0x00,0x7e,0x00,0x00,0xe0,0xff,0x01,0xf0,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0x00,0x1f,0x00,0x00,0xf8,0xff,0x00,0xf8,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0xc0,0x0f,0x00,0x00,0xfe,0x7f,0x00,0xfc,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0xe0,0x03,0x00,0x80,0xff,0x1f,0x00,0xfe,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0xf8,0x01,0x00,0xe0,0xff,0x07,0x00,0xfe,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0x7c,0x00,0x00,0xfc,0xff,0x00,0x00,0xfc,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0x3e,0x00,0x00,0xff,0x07,0x00,0x00,0xfc,0xff,0xff,0xff,0x7f,
0xff,0xff,0x7f,0x00,0x0f,0x00,0xc0,0xff,0x07,0x00,0x00,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x80,0x07,0x00,0xf0,0xff,0xff,0x0f,0xc0,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xc0,0x03,0x00,0xf8,0xff,0xff,0x3f,0xf8,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xc0,0x01,0x00,0xfe,0xf8,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xe1,0x01,0x00,0x7f,0xc0,0x03,0x87,0x00,0xfe,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xe1,0x00,0xc0,0x7f,0x80,0x01,0x86,0x00,0xfe,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x63,0x00,0xe0,0x7f,0x80,0x01,0x86,0x00,0xfe,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x63,0x00,0xe0,0x7f,0x8c,0x31,0x86,0xc3,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x67,0x00,0xc0,0x7f,0x8c,0x31,0x86,0x83,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x6f,0x00,0xc0,0x7f,0x8c,0x31,0x86,0x83,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x7f,0x00,0xc0,0x7f,0x8c,0x31,0x86,0x83,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0x7f,0x00,0xc0,0x7f,0x8c,0x31,0x86,0x83,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x00,0x80,0x7f,0x80,0x01,0x86,0x83,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x01,0x00,0x7f,0x80,0x01,0x86,0x83,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x03,0x00,0x7c,0xc0,0x03,0x87,0x83,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x07,0x00,0xf8,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x0f,0x00,0xe0,0xff,0x7f,0xf0,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x3f,0x00,0x00,0xfe,0x07,0xfc,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0x7f,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0x03,0x00,0x00,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0x0f,0x00,0x00,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0x7f,0x00,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f
};
//GPIO4(SDA) GPIO5(SCL) 
OLED display(4, 5);

void setup() {
  //初始化oled
  display.begin();

  //测试显示信息
  display.print("Hello ESP8266");
  display.print("From OLED example",2,0);
  delay(3*1000);

  // 测试清除
  display.clear();
  
  for(int i=0; i<1024; i++){
    Wire.beginTransmission(0x3C); // begin transmitting
    Wire.write(0x40);//data mode
    Wire.write(logo[i]);
    Wire.endTransmission();  
  }

}

void loop() {
}
