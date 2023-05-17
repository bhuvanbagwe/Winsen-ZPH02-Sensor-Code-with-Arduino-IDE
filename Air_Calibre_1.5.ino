// Winsen ZPH02 PM 2.5 Sensor Code 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pulsePin # (or -1 if sharing Arduino reset pulsePin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int pulsePin = D0; // set the pulsePin ( Digital Pin will do )

float duty_c =0;
float pm;
float duration;
int pm_send;

void setup() {

  MySerial.begin(9600, SERIAL_8N1, -1, -1); // My Serial for Transmitting over Bluetooth via UART ( Rx and Tx )
  Serial.begin(9600); // Serial Monitor for personal referrence of sensor data during debugging 
  
  pinMode(pulsePin,INPUT); // Set the Pulse pin as an INPUT 

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.setTextColor(WHITE);
  delay(10);
}


void loop() 
  {

  duration = pulseIn(pulsePin, LOW);
  duty_c = (duration/(6000000))*100;
  pm = map(duty_c, 0,100,0,1000); // To be configured ^^^ ^^^ ^^^ ^^^

  pm_send =  (int)(pm+0.5);
  Serial.print(1);
  Serial.println(pm_send);
  MySerial.print(1);
  MySerial.println(pm_send);

  display.setCursor(0,0);
  display.print("  -- Air Calibre --");

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print(String(pm)+" ug/cm^3");
  MySerial.print(1); // Start bit for Bluetooth connection
  MySerial.print(i);
  delay(100);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print(String(pm)+" ug/cm^3");
  MySerial.print(1); // Start bit for Bluetooth connection
  MySerial.print(i);

  if (pm < 1000 && pm> 0) 
  {
  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("    - Clean Air -     "); 
  }

  if (pm > 55 && pm < 100) {

  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("    - Not good for sensitive groups. -     "); 
    }

  if (pm > 100 && pm < 150)
  {
  display.setTextSize(1);
  display.setCursor(0,20);
//  display.print("          ");
  display.print("  - Unhealthy -  "); 
  }

  if (pm > 150 && pm < 250) 
  {
  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("    - Very Unhealthy -     "); 
  }

 if (pm > 250 ) 
 `{
  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("    - Hazard -    "); 
 `}
  display.display();
  }
