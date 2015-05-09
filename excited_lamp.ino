#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <RTC_DS3231.h>
 


//####################
// I/O
//#####################
const int RLedPin =  5;      //Red LED
const int GLedPin =  6;      //Green LED
const int BLedPin =  9;      //Blue LED

const int SW1Pin  =  15;      //Switch 1
const int SW2Pin  =  16;      //Switch 2
const int SW3Pin  =  18;      //Switch 3
const int SW4Pin  =  19;      //Switch 4

LiquidCrystal lcd(0, 1, 4, 7, 8, 14); //LCD pin description (RS, EN, D4, D5, D6, D7)

//####################
// Variables
//#####################
int SW1State = 0;
int SW2State = 0;
int SW3State = 0;
int SW4State = 0;

RTC_DS3231 RTC; //Name of the RTC module?


//####################################################################################
// SETUP
//####################################################################################
void setup() {
    pinMode(RLedPin, OUTPUT);
    pinMode(GLedPin, OUTPUT);
    pinMode(BLedPin, OUTPUT);
    
    pinMode(SW1Pin, INPUT_PULLUP);
    pinMode(SW2Pin, INPUT_PULLUP);
    pinMode(SW3Pin, INPUT_PULLUP);
    pinMode(SW4Pin, INPUT_PULLUP);
    
    lcd.begin(16, 2);
    
    Serial.begin(9600);
    
    //####################
    // RTC Setup
    //#####################
    Wire.begin();
    RTC.begin();
  
    if (! RTC.isrunning()) {
      Serial.println("RTC is NOT running!");
      // following line sets the RTC to the date & time this sketch was compiled
      RTC.adjust(DateTime(__DATE__, __TIME__));
    }
  
    DateTime now = RTC.now();
    DateTime compiled = DateTime(__DATE__, __TIME__); //Retrieves compile time
    if (now.unixtime() < compiled.unixtime()) { //RTC is older than compile time
      RTC.adjust(DateTime(__DATE__, __TIME__));
    }
//    char datastr[100];
//    RTC.getControlRegisterData( datastr[0]  );
}


//####################################################################################
// MAIN
//####################################################################################
void loop() {
  
  //Get RTC 
  DateTime now = RTC.now();
  float temp_float = RTC.getTempAsFloat();
  int16_t temp_word = RTC.getTempAsWord();
  int8_t temp_hbyte = temp_word >> 8; //Get the 8 MSB 0x(XX00) of the temperature
  int8_t temp_lbyte = (temp_word &= 0x00F0) >> 4; //Get the 0x(00X0) of the temperature
  
  //To be removed (Having fun with LEDs)
          SW1State=digitalRead(SW1Pin);
          SW2State=digitalRead(SW2Pin);
          SW3State=digitalRead(SW3Pin);
          SW4State=digitalRead(SW4Pin);
          if(SW1State==0) {
            digitalWrite(RLedPin, HIGH);    
            delay(100);             
            digitalWrite(GLedPin, HIGH);    
            delay(100);                
            digitalWrite(BLedPin, HIGH);    
            delay(100);                   
            digitalWrite(RLedPin, LOW);   
            delay(100);           
            digitalWrite(GLedPin, LOW);   
            delay(100);           
            digitalWrite(BLedPin, LOW);   
            delay(100);
          }
          if(SW2State==0) {
            digitalWrite(RLedPin, HIGH);    
          }
          else  digitalWrite(RLedPin, LOW);  
          if(SW3State==0) {
            digitalWrite(GLedPin, HIGH);    
          }
          else  digitalWrite(GLedPin, LOW);    
          if(SW4State==0) {
            digitalWrite(BLedPin, HIGH);    
          }
          else  digitalWrite(BLedPin, LOW);      
          delay(10);
  
  
  //####################
  // Update LCD
  //#####################
  lcd.setCursor(0, 0);
  if(now.hour()<10) lcd.print('0'); //Force 2 digits display
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  if(now.minute()<10) lcd.print('0');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  if(now.second()<10) lcd.print('0');
  lcd.print(now.second(), DEC);
  
  lcd.print("   ");
  if((now.month()-7)<10) lcd.print('0'); //Unknown source offset compensated
  lcd.print(now.month()-7, DEC);
  lcd.print('/');
  if(now.day()<10) lcd.print('0');
  lcd.print(now.day(), DEC);
  
  lcd.setCursor(0, 1);
  if(temp_hbyte<10) lcd.print('0');
  lcd.print(temp_hbyte, DEC);
  lcd.print(".");
  lcd.print(temp_lbyte, DEC);
  lcd.print("C");
  
  
  delay(1000);
}
