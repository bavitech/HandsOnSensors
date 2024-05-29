// TCS34725.ino, V Ziemann, 221006
#include <Wire.h>    // include support for the I2C functionality
const int TCS34725=0x29;                      // I2C address
int led = 2;                                  // LED on breakout board
void I2Cwrite(int addr, int reg, int val) {   // I2C write
  Wire.beginTransmission(addr);               // address
  Wire.write(0xFF & (0x80 | reg));            // register with command bit set
  Wire.write(val);                            // write value
  Wire.endTransmission(true);
}
void setup() {
  Wire.begin();                               // initialize the I2C functionality
  Serial.begin(9600); while (!Serial) {;}
  pinMode(led,OUTPUT);                        // control the LED on breakout board
  digitalWrite(led,LOW);                      // initially it is off
  delay(10);                                  // wait
  I2Cwrite(TCS34725,0x00,0x01);               // first PON
  delay(3);                                   // see note 2 on page 20
  I2Cwrite(TCS34725,0x00,0x03);               // then AEN
}
void loop() {
    int b1,b2,clear,red,green,blue;
    digitalWrite(led, HIGH); delay(100);
    Wire.beginTransmission(TCS34725);
    Wire.write(0xFF & (0x80 | 0x14));            // start register address
    Wire.endTransmission(false);
    Wire.requestFrom(TCS34725,8);                // request eight bytes in a row
    b1=Wire.read(); b2=Wire.read(); clear=b2*256+b1; 
    b1=Wire.read(); b2=Wire.read(); red=b2*256+b1; 
    b1=Wire.read(); b2=Wire.read(); green=b2*256+b1; 
    b1=Wire.read(); b2=Wire.read(); blue=b2*256+b1; 
    Serial.print(clear); Serial.print("\t");
    Serial.print(red); Serial.print("\t "); 
    Serial.print(green); Serial.print("\t "); Serial.println(blue);
    digitalWrite(led, LOW);    
    delay(1000);   
}
