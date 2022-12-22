
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <String>

// Replace with your network credentials
const char *ssid     = "Verizon_D4BTLH";
const char *password = "sift6-elm-gains";
const long utcOffsetInSeconds = -18000; // NJ   https://en.wikipedia.org/wiki/List_of_UTC_offsets  UTC offet*60*60
//const long utcOffsetInSeconds = -18000; // NJ


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(){
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();
  
  Serial.println("/");
  Serial.println(daysOfTheWeek[timeClient.getDay()]);
  Serial.println("#");
  Serial.println(get_hours(timeClient.getHours()));
  Serial.println("#");
  Serial.println(timeClient.getMinutes());
  Serial.println("#");
  Serial.println(getDate());
  Serial.println("#");
  Serial.println(getMonth());
  Serial.println("#");
  Serial.println(getYear());
  delay(3000);
}

int getYear() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  int year = ti->tm_year + 1900;
  
  return year;
}

int getMonth() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  int month = (ti->tm_mon + 1) < 10 ? 0 + (ti->tm_mon + 1) : (ti->tm_mon + 1);
  
  return month;
}

int getDate() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  int month = (ti->tm_mday) < 10 ? 0 + (ti->tm_mday) : (ti->tm_mday);
  
  return month;
}

int get_hours(int hh){
    // Handle 00 and 12 case separately
        if (hh > 12) {
          hh-=12;
        }
return hh;
}
