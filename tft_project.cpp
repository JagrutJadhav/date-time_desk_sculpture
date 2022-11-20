
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h>
#include <stdint.h>
#include "TouchScreen.h"
#include <SoftwareSerial.h>
#include <Fonts/FreeSerif9pt7b.h>

SoftwareSerial mySerial(10, 12); // RX, TX


// These are the pins for the shield!
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin
bool dst = true;
bool sts = true;


#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define BLACK  0x0000  //white
#define BLUE    0x001F //cyan
#define RED     0xF800 //yellow
#define GREEN   0x07E0 //Magenta
#define CYAN    0x07FF  //blue
#define MAGENTA 0xF81F //green
#define YELLOW  0xFFE0 //red
#define WHITE   0xFFFF  //white

char *color[] = {BLACK, BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE};
char *color_sel[] = {CYAN, MAGENTA, YELLOW};
int run_iter =0;
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;
String day = "SUNDAY";
String date = "17";
String month = "May";
String year = "2022";
String hour = "12";
String minuite = "00";
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillis_time = 0; 
const long interval = 35000;  // time to display
const long interval_time = 15000;
int val = 0; 
bool state = false;
bool sts_2 = false;
char cha;
String ser;
int count =0;
unsigned long currentMillis = millis();
unsigned long currentMillis_time = millis();
const int buttonPin = 11;
int buttonState = 0;
int rand_col = CYAN;
void setup(void) {
  Serial.begin(9600);
#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
#endif
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  mySerial.begin(9600);
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();
  tft.invertDisplay(0);

  tft.begin(0x8357);
//tft.begin(0x5408);
Serial.println(tft.readID());
tft.setRotation(2);
tft.fillScreen(WHITE);
tft.setTextColor(BLACK);
tft.setCursor(0,100);
tft.setTextSize(5);//11 
pinMode(buttonPin, INPUT);
buttonState = digitalRead(buttonPin);
Serial.print("BUTTON STATE = ");
Serial.println(buttonState);
if (buttonState == HIGH) {
    // turn LED on:
    Serial.println("DST is on");
    tft.print("DST -    True");
    dst = true;
  } else {
    // turn LED off:
    Serial.println("DST is off");
    tft.print("DST -    False");
    dst= false;
  }
  delay(2000);
  tft.fillScreen(WHITE);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);//11
  tft.setCursor(0,100);
  tft.print("Getting Date..") ;
  delay(1000);
  
}

void loop(void) {  
  
 if (mySerial.available()) {
    //Serial.write(mySerial.read())
    int dec;
    dec = mySerial.read();
    cha = (char)dec;

    if (cha == '/'){
      count = 0;
      ser = "";
      Serial.print("Day ");
  Serial.println(day);
  Serial.print("Hour ");
  Serial.println(hour);
  Serial.print("Min ");
  Serial.println(minuite);
  Serial.print("Date ");
  Serial.println(date);
  Serial.print("Month ");
  Serial.println(month);
  Serial.print("Year ");
  Serial.println(year);
    if(run_iter == 0){
    run_iter = 1;
    testText(hour,minuite,day,date,month,year);}

    }
    else{
       if(cha == '#'){
        Serial.println(count);
        Serial.println(ser);
        switch(count) {
        case 0:
        //day = ser;
          
              if (ser == "Monday"){
                 day ="MONDAY";
              }
              else if (ser == "Tuesday"){
                 day ="TUESDAY";
              }
              else if (ser == "Wednesday"){
                 day ="WEDNESDAY";
              }
              else if (ser == "Thursday"){
                 day ="THURSDAY";
              }
              else if (ser == "Friday"){
                 day ="FRIDAY";
              }
              else if (ser == "Saturday"){
                 day ="SATURDAY";
              }
              else if (ser == "Sunday"){
                 day ="SUNDAY";
              }
          
        break; 
        case 1:
        if (dst == true){
          if (ser == "1") hour = "02";
          else if (ser == "2") hour = "03";
          else if (ser == "3") hour = "04";
          else if (ser == "4") hour = "05";
          else if (ser == "5") hour = "06";
          else if (ser == "6") hour = "07";
          else if (ser == "7") hour = "08";
          else if (ser == "8") hour = "09";
          else if (ser == "9") hour = "10";
          else if (ser == "10") hour = "11";
          else if (ser == "11") hour = "12";
          else if (ser == "0") hour = "01";
          else hour = ser;
        }
        else {
          if (ser == "1") hour = "01";
          else if (ser == "2") hour = "02";
          else if (ser == "3") hour = "03";
          else if (ser == "4") hour = "04";
          else if (ser == "5") hour = "05";
          else if (ser == "6") hour = "06";
          else if (ser == "7") hour = "07";
          else if (ser == "8") hour = "08";
          else if (ser == "9") hour = "09";
          else if (ser == "10") hour = "10";
          else if (ser == "11") hour = "11";
          else if (ser == "0") hour = "12";
          else hour = ser;
        }
        break;
        case 2:
        //minuite = ser;
          if (ser == "0") minuite = "00";
          else if (ser == "1") minuite = "01";
          else if (ser == "2") minuite = "02";
          else if (ser == "3") minuite = "03";
          else if (ser == "4") minuite = "04";
          else if (ser == "5") minuite = "05";
          else if (ser == "6") minuite = "06";
          else if (ser == "7") minuite = "07";
          else if (ser == "8") minuite = "08";
          else if (ser == "9") minuite = "09";
          else minuite = ser;
        break;
        case 3:
        month = ser;
        break;
        case 4:
        date = ser;
        break;
        case 5:
        year = ser;
        break;
        default:{}
      }
     
        count++;
        ser = "";
      }
      else{
      if (dec != 10 && dec != 13){
        ser.concat(cha);
        }
      }
          
    }
    //Serial.write (cha);
  }
  currentMillis_time = millis();
  if (currentMillis_time - previousMillis_time >= interval) {
  // save the last time you blinked the LED
  graphics();
  //previousMillis_time = currentMillis_time;
  previousMillis_time = millis();
  run_iter = 0;
  }
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(BLACK);
  tft.fillScreen(RED);
  tft.fillScreen(GREEN);
  tft.fillScreen(BLUE);
  tft.fillScreen(BLACK);
  return micros() - start;
}

unsigned long testText(String hour_1, String minuite_1,String day_1,String date_1,String month_1,String year_1) {
  tft.fillScreen(WHITE);
  Serial.print("Randpm Colour = ");
  Serial.println(rand_col);
  rand_col = color_sel[random(3)];
  //unsigned long start = micros();
  tft.setFont();
  //tft.fillCircle(120,-80, 280, BLACK);
  tft.fillCircle(120,-80, 275, BLACK);
  for (int x = 0; x < 250; x += 14) {
        for (int y = 120; y < 210; y += 14) {
            tft.drawCircle(x, y, 7, WHITE);
        }
    }
  tft.fillCircle(120,-80, 252, WHITE);
  tft.fillCircle(120,-80, 243, rand_col);
  tft.fillRect(0, 0, 240, 25, BLACK);
  tft.fillRect(0, 25, 240, 9, WHITE);
  for (int x = 0; x < 250; x += 14) {
        for (int y = 7; y < 28; y += 14) {
            tft.drawCircle(x, y, 7, WHITE);
        }
    }
  tft.setCursor(2,50);
  //tft.println();
  //tft.println();
  //tft.println();
  tft.setTextColor(BLACK);  
  tft.setTextSize(10.6);//11
  tft.print(hour_1);
  tft.setTextSize(6);//6
  tft.setCursor(115,70);
  tft.print(":");
  tft.print(minuite_1);
  tft.println();
  //tft.fillRect(0, 160, 240, 7, YELLOW);
  tft.setFont(&FreeSerif9pt7b);
  tft.setCursor(0, 240);
  tft.setTextColor(BLACK);
  tft.setTextSize(2.8);//5
  tft.println(day_1);
  tft.setCursor(0, 295);
  tft.setTextColor(rand_col);
  tft.setTextSize(2);//3.2
  tft.print(date_1);
  tft.print("-");
  tft.print(month_1);
  tft.print("-");
  tft.print(year_1);
  
 // return micros() - start;
}



void circles(){
  tft.drawCircle(random(0,480), random(0,320), random(10, 40), color[random(1, 8)]);
 delay(250);
}

void graphics(){
  //Serial.print(F("Lines                    "));
  //Serial.println(testLines(color[random(1, 8)]));
  //delay(500);

 // Serial.print(F("Horiz/Vert Lines         "));
  Serial.println(testFastLines(color[random(2, 7)], color[random(2, 7)]));
  delay(500);

  //Serial.print(F("Rectangles (outline)     "));
  //Serial.println(testRects(GREEN));
  //delay(500);

  //Serial.print(F("Rectangles (filled)      "));
  //Serial.println(testFilledRects(color[random(1, 8)], color[random(1, 8)]));
  //delay(500);

  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, color[random(2, 7)]));

  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, color[random(2, 7)]));
  delay(500);
/*
  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(500);

  //Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(500);
*/
}



unsigned long testLines(uint16_t color) {
    unsigned long start, t;
    int           x1, y1, x2, y2,
                  w = tft.width(),
                  h = tft.height();

    tft.fillScreen(WHITE);

    x1 = y1 = 0;
    y2    = h - 1;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
    x2    = w - 1;
    for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
    t     = micros() - start; // fillScreen doesn't count against timing

    tft.fillScreen(WHITE);

    x1    = w - 1;
    y1    = 0;
    y2    = h - 1;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
    x2    = 0;
    for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
    t    += micros() - start;

    tft.fillScreen(WHITE);

    x1    = 0;
    y1    = h - 1;
    y2    = 0;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
    x2    = w - 1;
    for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
    t    += micros() - start;

    tft.fillScreen(WHITE);

    x1    = w - 1;
    y1    = h - 1;
    y2    = 0;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
    x2    = 0;
    for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

    return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
    unsigned long start;
    int           x, y, w = tft.width(), h = tft.height();

    tft.fillScreen(WHITE);
    start = micros();
    for (y = 0; y < h; y += 5) {
    tft.drawFastHLine(0, y, w, color1);
    delay(50);
    }
    for (x = 0; x < w; x += 5){
      tft.drawFastVLine(x, 0, h, color2);
      delay(50);
    }

    return micros() - start;
}

unsigned long testRects(uint16_t color) {
    unsigned long start;
    int           n, i, i2,
                  cx = tft.width()  / 2,
                  cy = tft.height() / 2;

    tft.fillScreen(WHITE);
    n     = min(tft.width(), tft.height());
    start = micros();
    for (i = 2; i < n; i += 6) {
        i2 = i / 2;
        tft.drawRect(cx - i2, cy - i2, i, i, color);
    }

    return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
    unsigned long start, t = 0;
    int           n, i, i2,
                  cx = tft.width()  / 2 - 1,
                  cy = tft.height() / 2 - 1;

    tft.fillScreen(WHITE);
    n = min(tft.width(), tft.height());
    for (i = n; i > 0; i -= 6) {
        i2    = i / 2;
        start = micros();
        tft.fillRect(cx - i2, cy - i2, i, i, color1);
        t    += micros() - start;
        // Outlines are not included in timing results
        tft.drawRect(cx - i2, cy - i2, i, i, color2);
    }

    return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
    unsigned long start;
    int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

    tft.fillScreen(WHITE);
    start = micros();
    for (x = radius; x < w; x += r2) {
        for (y = radius; y < h; y += r2) {
            tft.fillCircle(x, y, radius, color);
        }
    }

    return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
    unsigned long start;
    int           x, y, r2 = radius * 2,
                        w = tft.width()  + radius,
                        h = tft.height() + radius;

    // Screen is not cleared for this one -- this is
    // intentional and does not affect the reported time.
    start = micros();
    for (x = 0; x < w; x += r2) {
        for (y = 0; y < h; y += r2) {
            tft.drawCircle(x, y, radius, color);
        }
    }

    return micros() - start;
}

unsigned long testTriangles() {
    unsigned long start;
    int           n, i, cx = tft.width()  / 2 - 1,
                        cy = tft.height() / 2 - 1;

    tft.fillScreen(WHITE);
    n     = min(cx, cy);
    start = micros();
    for (i = 0; i < n; i += 5) {
        tft.drawTriangle(
            cx    , cy - i, // peak
            cx - i, cy + i, // bottom left
            cx + i, cy + i, // bottom right
            tft.color565(0, 0, i));
    }

    return micros() - start;
}

unsigned long testFilledTriangles() {
    unsigned long start, t = 0;
    int           i, cx = tft.width()  / 2 - 1,
                     cy = tft.height() / 2 - 1;

    tft.fillScreen(WHITE);
    start = micros();
    for (i = min(cx, cy); i > 10; i -= 5) {
        start = micros();
        tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                         WHITE);
        t += micros() - start;
        tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                         BLACK);
    }

    return t;
}

