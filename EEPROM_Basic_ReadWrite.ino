
/*
This sketch reads/writes from/to EEPROM using the serial monitor.

Limitations: This sketch will only write to one address bit at a time. you can only enter a value from 0 to 255 to read into EEPROM

I originaly wrote this sketch for a class assigment

*/

#include <EEPROM.h>

String inputString = "";
char incomingByte;
int content = 0;
int address = 0;


//function
int readfromEEPROM(int address){
  int value = -0;
  if(address >= 0 && address <= EEPROM.length())
     value = EEPROM.read(address);
  return value;
 }

 void wrtieToEEPROM(int address, int value){
  //
  if(address >= 0 && address <= 1023)
    EEPROM.write(address, value);
  return;
 }

  
void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0){
    //
    incomingByte = Serial.read();
    inputString = inputString + incomingByte;
    // say what you got:
    inputString.toLowerCase();
    
  }
  //if the user types in the read command, then 
   if ((inputString.substring(0, 4) == "read") && (inputString.length() > 5  && inputString.length() < 10 )){
      //
      String addr = inputString.substring(4, inputString.length());
      addr.trim();
      address = addr.toInt();
      Serial.print("Reading from EEPROM - Address: ");
      Serial.println(address, DEC);
      Serial.print("Value: ");
      Serial.println(readfromEEPROM(address), DEC);
      Serial.println("==========================");
      inputString = ""; 
   }  


   if ((inputString.substring(0,5) == "write") && (inputString.length() > 8 && inputString.length() < 15)){
      String addr = inputString.substring(5, inputString.length());
      String cnt = inputString.substring(5, inputString.length());
      String laddr = "";
      String lval = "";
      addr.trim();
      cnt.trim();
      int gappos = 0;
      //      
      
      for(int i = 0; i < addr.length(); i++){
          if(addr[i] == ' '){
            gappos = i;
          }
      }
      //
      laddr = addr.substring(0, (gappos + 1));
      lval = addr.substring(gappos, addr.length()); 
      //
      address = laddr.toInt();
      content = lval.toInt();
      //
      Serial.print("Writing to EEPROM - Address: ");
      Serial.println(address, DEC);
      Serial.print("Value: ");
      Serial.println(content, DEC);
      wrtieToEEPROM(address, content);
      Serial.println("==========================");
      inputString = ""; 
   }  

   inputString = "";
    delay(2000);
  
}// end loop
