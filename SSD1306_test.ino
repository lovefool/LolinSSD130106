/*******************************************************************************
 * Sketch name: SSD1306 test program
 * Description: 
 * Created on:  2023.12.19
 * Author:      Jay Teramoto
 * Book:        Electronics Projects with the ESP8266 and ESP32
 * Chapter :    12 - GPS tracking app with Google Maps
 ******************************************************************************/

/*******************************************************************************
 * Sketch name: Signal reception to monitor nRF24L01 transceiver modules
 * Description: assess reception of "standard" transmitted signal
 * Created on:  October 2020
 * Author:      Neil Cameron
 * Book:        Electronics Projects with the ESP8266 and ESP32
 * Chapter :    12 - GPS tracking app with Google Maps
 ******************************************************************************/


#include <Adafruit_SSD1306.h>       // library 12864 OLED screen
int width = 128;            // OLED screen dimensions
int height = 64;
Adafruit_SSD1306 oled(width, height, &Wire, -1);

const int Nval = 20;          // size of circular buffer
int pkts[Nval], sents[Nval];        // arrays for circular buffer
int N = 0, pkt = 0;
unsigned long sumPkt = 0, sumSent = 0;
float avgPkt=0.0, avgSent=0.0;
unsigned long lastTime, nowTime = 0;    // variables to store time values

void setup()
{
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();          // initialise OLED screen
  oled.setTextColor(WHITE);
  oled.display();
  
  for (int i=0; i<10; i++)        // set circular buffer arrays to zero
  {
    pkts[i] = 0;
    sents[i] = 0;
  }
}

void loop()
{
  nowTime = millis();
  if(nowTime - lastTime > 1000)     // update values every second
  {
    pkt += 1;
    avgPkt += 1.0;     // calculate moving averages
    avgSent += 2.0;
    screen();           // call OLED screen function
    lastTime = nowTime;         // update time of last "second"
  }
}

void screen()
{
  oled.clearDisplay();          // clear display

  oled.setCursor(0,0);          // position cursor
  oled.setTextSize(2);          // text size of 1216 pixels
  oled.print("PPS: ");oled.print(pkt);    // signal (packets) per second
  
  oled.setCursor(0,16);
  oled.setTextSize(1);          // text size of 68 pixels
  oled.setCursor(0,16);
  oled.print("avg");
  oled.setCursor(40,16);
  oled.print(avgSent,0);        // average of transmitted signals
  oled.setCursor(80,16);
  oled.print(avgPkt,0);         // average of received signals
  

  // oled.setCursor(0,25);
  // oled.print("sent");
    
  oled.display();
}
