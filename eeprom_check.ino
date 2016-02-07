#include <EEPROM.h>
#include <avr/sleep.h>

void setup()
{
  /*  Check EEPROM by writing multiple patterns and confirmimg the stored values
   *  By Pedro Ribeiro pamribeirox@gmail.com
   *  Based on EEPROM library examples
   *  December 2015
   */
  /***
    Iterate through each byte of the EEPROM storage.    
    
    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.
    
   ***/
  
  byte patt[] = { 0x00, 0xFF, 0x55, 0xAA, 0x00 };
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("EEPROM TEST BY Pedro Ribeiro");
  delay(5000);
  Serial.print("EEPROM DETECTED SIZE: ");
  Serial.println(EEPROM.length());
  for ( int p = 0; p < sizeof(patt)/sizeof(patt[0]) ; p++) {
    int i;
    Serial.print("TEST WITH: ");
    if(p) Serial.println(patt[p],HEX);
    else Serial.println("8 bit LSB ADDR");
    Serial.print(" WRITE: ");
    for (i = 0 ; i < EEPROM.length() ; i++ ) {
      EEPROM.write(i, p?patt[p]:i&0xFF);
      if(i % 128 == 0) Serial.print("W");
    }
    Serial.print(" ");
    Serial.print(i);
    Serial.println(" bytes");

    Serial.print(" READ: ");
    for (i = 0 ; i < EEPROM.length() ; i++ ) {
     if(EEPROM.read(i) != (p?patt[p]:i&0xFF)) {
       Serial.print(" ERROR AT ");
       Serial.print(i);
       Serial.print(" VALUE ");
       Serial.print(EEPROM.read(i));
       Serial.print(" != ");
       Serial.print(p?patt[p]:i&0xFF);
       Serial.println(" EXPECTED ");
       while(1) {
          digitalWrite(13, HIGH);
          delay(1000);
          digitalWrite(13, LOW);
          delay(1000);         
       };
      }
      if(i % 128 == 0) Serial.print("R");
    }
    Serial.print(" ");
    Serial.print(i);
    Serial.println(" bytes OK");
  }
  Serial.println("EEPROM OK");
  // turn the LED on when we're done
  digitalWrite(13, HIGH);
  Serial.flush();
  // HALT
  cli();
  sleep_enable();
  sleep_cpu();
}

void loop(){ /** Empty loop. **/ }
