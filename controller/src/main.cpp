#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "clock_manager.h"
#include "digits.h"
#include "web_server.h"
#include "ntp.h"

const char *ssid = "Crookienet_b22";
const char *password = "Crookshanks4301";

ClockWebServer web_server;

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.

  Serial.begin(9600);
  Serial.println("Booting");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA
      .onStart([]()
               {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type); })
      .onEnd([]()
             { Serial.println("\nEnd"); })
      .onProgress([](unsigned int progress, unsigned int total)
                  { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
      .onError([](ota_error_t error)
               {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  begin_NTP();
  setSyncProvider(get_NTP_time);
  // Sync every 30 minutes
  setSyncInterval(60 * 30);

  Wire.begin();
  web_server.begin(&clock_manager);

  clock_manager.setHourDirection(CLOCKWISE1);
  clock_manager.setMinuteDirection(COUNTERCLOCKWISE1);
  clock_manager.setHourSpeed(800.0);
  clock_manager.setMinuteSpeed(1400.0);

  clock_manager.sendFullClocks();
  // delay(15000);

  pinMode(LED_BUILTIN, OUTPUT);
}

int digit_index = 0;
unsigned long time_last;
int last_hour = -1;
int last_minute = -1;

#define SECOND 1000

// the loop function runs over and over again forever
void loop()
{
  ArduinoOTA.handle();
  web_server.update();

  if (last_hour != hour() || last_minute != minute())
  {
    last_hour = hour();
    last_minute = minute();
    clock_manager.setTime(last_hour, last_minute);
    if (clock_manager.getConfig().set_mode != MANUAL)
    {
      clock_manager.sendFullClocks();
    }
  }
}