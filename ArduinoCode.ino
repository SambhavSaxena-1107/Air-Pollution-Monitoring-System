#include "MQ135.h"
 //OLED Display libraries
 #include <SPI.h>
 #include <Wire.h>
 #include <Adafruit_GFX.h>
 #include <Adafruit_SSD1306.h>

 #define SCREEN_WIDTH 128    // OLED display width, in pixels
 #define SCREEN_HEIGHT 64    // OLED display height, in pixels
 #define OLED_RESET 4  
      
 Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 //In and Out
 int RedLed = 9;
 int GreenLed = 8;
 int Buzzer = 7;

void setup()
 {
  pinMode(RedLed, OUTPUT);   // initialize digital pin RedLed as an output.
  pinMode(GreenLed, OUTPUT); // initialize digital pin GreenLed as an output.
  pinMode(Buzzer, OUTPUT);   // initialize digital pin Buzzer as an output.
  // Start serial communication between arduino and your computer
  Serial.begin(9600); 
  //initialize with the I2C addr 0x3C (128x64)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  delay(10);
  
  // Print text on display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("ELECTRODUIN0"); // Print text
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("Air Pollution");
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,35);
  display.println(" Monitoring");
  display.display();
  delay(2000);
 }


void loop()
 {
  // Read Senso value
  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();
  // Print Senso value on Serial Monitor Window
  Serial.print("Air Quality: ");  
  Serial.print(air_quality);
  Serial.println("  PPM");   
  Serial.println();
  //Print Senso value or Air Quality Index on OLED Display
  display.clearDisplay();
  display.setCursor(0,0);  //oled display position
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Air Quality Index");
  display.setCursor(0,20);  //oled display position
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(air_quality);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" PPM");
  display.display();
    // when air quality value less than 1000PPM 
    if (air_quality<=1000)
     {
      digitalWrite(GreenLed, HIGH); // turn the Green LED on
      digitalWrite(RedLed,LOW);    // turn the Red LED off
      noTone(Buzzer);              // turn the Buzzer off
      // Print text on OLED Display
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,45);
      display.println("Fresh Air"); //Message
      display.display();
      delay(2000);
     }
    // when air quality value greater than 1000PPM & less than 2000PPM  
    else if( air_quality>=1000 && air_quality<=2000 )
     {
      digitalWrite(GreenLed,LOW);  // turn the Green LED off
      digitalWrite(RedLed, HIGH ); // turn the Red LED on
      noTone(Buzzer);              // turn the Buzzer off 
      // Print text on OLED Display
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,45);
      display.println(" Poor Air"); //Message
      display.display();
      delay(2000);      
     }
    // when air quality value greater than 2000PPM 
    else if (air_quality>=2000 )
     {
      digitalWrite(GreenLed,LOW);  // turn the Green LED off
      digitalWrite(RedLed,HIGH);   // turn the Red LED on
      tone(Buzzer, 1000, 200);     // turn the Buzzer on
      // Print text on OLED Display
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,45);
      display.println("Danger!!"); //Message
      display.display();
      delay(2000);
     }
    }
