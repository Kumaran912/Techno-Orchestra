#include <SPI.h>
#include <SD.h>
int latchPin = 6;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 7;  // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 5; // Data pin of 74HC595 is connected to Digital pin 4
int CSpin = 4;
String leds="0000000000000000";    // Variable to hold the pattern of which LEDs are currently turned on or off
int tp = 500;// Half of the time period we have considered

File myFile;

void updateShiftRegister(String leds)
{
  int a = 0;
  int b = 1;
  for(int i=15;i>-1;i--)
  { 
    if(leds[i]=='1')
     a += b;
    b=b*2;
  } 
  digitalWrite(latchPin, LOW);
  Serial.println(a);
  shiftOut(dataPin, clockPin, MSBFIRST, a/256);
  shiftOut(dataPin, clockPin, MSBFIRST, a%256);
  digitalWrite(latchPin, HIGH);
}
void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);  // Open serial communications and wait for port to open:
  //digitalWrite(dataPin, LOW);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) 
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  myFile = SD.open("envisage.txt");  // open the file for reading:
  if (myFile) 
  {
    Serial.println("envisage.txt:");  // read from the file until there's nothing else in it:
    while (myFile.available()) 
    {
      leds = myFile.readStringUntil('\n');
      Serial.println(leds);
      updateShiftRegister(leds);
      delay(tp);
      leds = "0000000000000000" ;
      updateShiftRegister(leds);
      delay(tp);
    }
    // close the file:
    leds = "0000000000000000" ;
    updateShiftRegister(leds);
    myFile.close();
  } 
  else 
  {
    Serial.println("error opening test.txt"); // if the file didn't open, print an error:
  }
}

void loop()
{
}

/*open file
read from file till end of file
 leds = what is there in the line
 updateShiftRegister()
 delay(time period)
 leds=0
 updateShiftRegister()
close the file

void loop() 
{
  SD.begin(CSpin);
  myFile = SD.open("info.txt" , FILE_WRITE);
  leds = dataFile.read();
  
  updateShiftRegister();
  delay(tp);
  leds = 0 ;
  updateShiftRegister();
  delay(tp);
}
*/
