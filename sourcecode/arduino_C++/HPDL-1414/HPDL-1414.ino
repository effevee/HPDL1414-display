/* demo sketch with Arduino Nano and HPDL-1414 (4 Character Smart Alphanumeric Display)
 * datasheet on https://media.digikey.com/pdf/Data%20Sheets/Avago%20PDFs/HPDL-1414.pdf 
 * 
 * (c)2019 Frank Vergote
 */

#include "Arduino.h";

byte digit_sel[] = {2, 3};
byte data_in[] = {8, 9, 10, 11, 5, 6, 12};
byte wr_write = 4;

String gogoString = "    I LOVE MY HPDL-1414 DISPLAY ...    ";
byte stringLength = 0;
byte stringPos = 0;

void write_char(byte digit, byte ascii)
{
  // display off
  digitalWrite(wr_write, HIGH);
  // select digit 
  digitalWrite(digit_sel[0], 1 & digit);
  digitalWrite(digit_sel[1], 1 & digit>>1);
  // ascii code -> data_in
  digitalWrite(data_in[0], 1 & ascii>>0);
  digitalWrite(data_in[1], 1 & ascii>>1);
  digitalWrite(data_in[2], 1 & ascii>>2);
  digitalWrite(data_in[3], 1 & ascii>>3);
  digitalWrite(data_in[4], 1 & ascii>>4);
  digitalWrite(data_in[5], 1 & ascii>>5);
  digitalWrite(data_in[6], 1 & ascii>>6);
  // display on
  digitalWrite(wr_write, LOW);
  delay(5);
  // display off  
  digitalWrite(wr_write, HIGH);
  delay(5);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // pinnen initialiseren
  for (byte cnt = 0; cnt < sizeof digit_sel; cnt++) {
    pinMode(digit_sel[cnt], OUTPUT);
  }
  for (byte cnt = 0; cnt < sizeof data_in; cnt++) {
    pinMode(data_in[cnt], OUTPUT);
  }
  // display off
  pinMode(wr_write, OUTPUT);  
  digitalWrite(wr_write, HIGH);

  stringLength = gogoString.length();
}

void loop() {
  // put your main code here, to run repeatedly:
  // schrijf characters in omgekeerde volgorde
  write_char(3,int(gogoString[stringPos]));
  write_char(2,int(gogoString[stringPos+1]));
  write_char(1,int(gogoString[stringPos+2]));
  write_char(0,int(gogoString[stringPos+3]));
  // positie verhogen
  if(stringPos == stringLength - 4){
    stringPos = 0;
  }
  else{
    stringPos = stringPos + 1;
  }
  // even wachten
  delay(250); 
}
