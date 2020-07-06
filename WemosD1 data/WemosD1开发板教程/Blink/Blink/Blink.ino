

#define LED D4//引脚定义初始化

void setup() 
{
  Serial.begin(9600);//串口打开
  pinMode(LED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
 // digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  //delay(1000);                      // Wait for a second
  //digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  //delay(2000);  
  // Wait for two seconds (to demonstrate the active low LED)
  Serial.println("Hello world"); //println 打印
  delay(1000);
  digitalWrite(LED, LOW); 
  delay(2000);  
  digitalWrite(LED, HIGH); 
  delay(2000);  
  


  
}
