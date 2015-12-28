
/*
This sketch reads/writes from/to EEPROM using the serial monitor.
In the serial monitor the user should be able to type one of two commands: “read” and “write.
"Read" takes one argument, an EEPROM address. "Write" takes two arguments, an EEPROM address and a value.

For example, if the user types “read 3” then the contents of EEPROM address 3 should be printed to the serial monitor. 
If the user types “write 3 10” then the value 10 should be written into address 3 of the EEPROM.

Limitations: This sketch will only write to one address bit at a time. you can only enter a value from 0 to 255 to read into EEPROM


*/

#include <EEPROM.h>

String inputString = "";
char incomingByte;
int content = 0;
int address = 0;


//function that accepts an address between 0 and 1023 and returns the 
//value that is found in the given address
int readfromEEPROM(int address){
  int value = -0;
  if(address >= 0 && address <= EEPROM.length())
     value = EEPROM.read(address);
  return value;
 }


//function that accepts an address between 0 and 1023 and and a value between 0 and 255 and 
// writes that value to the given address
 void wrtieToEEPROM(int address, int value){
  //
  if(address >= 0 && address <= 1023)
    EEPROM.write(address, value);
  return;
 }

  
void setup() {
    // initializing the serial monitor and 
    //setting the baud rate
    Serial.begin(9600);
  
}

void loop() {
  
  // Read in the input from the serial monitor:
  while(Serial.available() > 0){
    //store char value into a string
    incomingByte = Serial.read();
    // concat the char value building up the full string
    inputString = inputString + incomingByte;
    // convert the string to lower case 
    inputString.toLowerCase();
    
  }
  //if the user types in the read command, then 
   if ((inputString.substring(0, 4) == "read") && (inputString.length() > 5  && inputString.length() < 10 )){
      //need to extract the number from the string
      String addr = inputString.substring(4, inputString.length());
      addr.trim();
      address = addr.toInt();
      Serial.print("Reading from EEPROM - Address: ");
      Serial.println(address, DEC);
      Serial.print("Value: ");
      //then read the value at the given address and print to the serial monitor
      Serial.println(readfromEEPROM(address), DEC);
      Serial.println("==========================");
      //clear the input string
      inputString = ""; 
   }  

  // if the user typed in the write command then
   if ((inputString.substring(0,5) == "write") && (inputString.length() > 8 && inputString.length() < 15)){
      String addr = inputString.substring(5, inputString.length());
      String cnt = inputString.substring(5, inputString.length());
      String laddr = "";
      String lval = "";
      addr.trim();
      cnt.trim();
      int gappos = 0;
      //      
      //need to determine where the blank char between the two numbers is
      for(int i = 0; i < addr.length(); i++){
          if(addr[i] == ' '){
            gappos = i;
          }
      }
      //then extract the first number string which is the address
      laddr = addr.substring(0, (gappos + 1));
      //extract the second number string which is the value
      lval = addr.substring(gappos, addr.length()); 
      //convert the number strings into integers
      address = laddr.toInt();
      content = lval.toInt();
      //
      Serial.print("Writing to EEPROM - Address: ");
      Serial.println(address, DEC);
      Serial.print("Value: ");
      Serial.println(content, DEC);
      //write the value into the address location specified
      wrtieToEEPROM(address, content);
      Serial.println("==========================");
      //clear the input string
      inputString = ""; 
   }  
    //clear the input string
   inputString = "";
    delay(2000);
  
}// end loop
