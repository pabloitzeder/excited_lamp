//test
#include <LiquidCrystal.h>
LiquidCrystal lcd(5,12,11,10,9,6);
const int K1 = 2; // first button
const int K2 = 4; // second button
const int K3 = 7; // third button
const int PIR = 8; // Passive Infrared Receptor signal
const int LED = 3; // PWM controlled LED
void setup(){
lcd.begin(16,2); // The LCD has 2 lines and 16 columns
pinMode(K1,INPUT);
pinMode(K2,INPUT);
pinMode(K3,INPUT);
pinMode(PIR,INPUT);
pinMode(LED,OUTPUT);
lcd.print("Setup succesful");
}
void loop(){
} 
