#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

byte noteON = 145;
byte noteOFF = 129;
int velocity;

void MIDImessage(byte command, byte data1, byte data2)
{
  Serial.write(command);
  Serial.write(data1);
  Serial.write(data2);
}

void setup() {
  Serial.begin(9600);
  tft.reset();  
  tft.begin(0x9341);
  tft.setRotation(1);
  tft.fillScreen(WHITE);
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000
int note1 = 60;

void loop() {
  TSPoint p = ts.getPoint();  //Get touch point
  
  while (p.z > 500) {
   velocity = p.z;   
   
   Serial.print("X = "); Serial.print(p.x);
   Serial.print("\tY = "); Serial.print(p.y);
   Serial.print("\n");
   
   p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
   p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
        
    //This is important, because the libraries are sharing pins
   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);
   MIDImessage(noteON, note1, velocity);
   delay(10);
   }
MIDImessage(noteOFF, note1, velocity);
}


