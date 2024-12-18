#include "web_server.h"

#include <ArduinoJson.h>
#include <TimeLib.h>

WebServer _server(80);

ClockWebServer::ClockWebServer() {}

void ClockWebServer::begin(ClockManager *clock_manager)
{
    _server.on("/", HTTP_GET, handle_get);
    _server.on("/set", HTTP_POST, handle_set);
    _server.on("/time", HTTP_GET, handle_get_time);
    _clock_manager = clock_manager;
    _server.begin();
    Serial.println("Server started");
}

void ClockWebServer::update()
{
    _server.handleClient();
}

void handle_get()
{
    config cfg = clock_manager.getConfig();
    
    String message = "{"; // Start JSON
    message = message + "\"hour_speed\":" + cfg.hour_speed + ",";
    message = message + "\"minute_speed\":" + cfg.minute_speed + ",";
    message = message + "\"hour_accel\":" + cfg.hour_accel + ",";
    message = message + "\"minute_accel\":" + cfg.minute_accel + ",";
    message = message + "\"hour_dir\":" + cfg.hour_direction + ",";
    message = message + "\"minute_dir\":" + cfg.minute_direction + ",";
    message = message + "\"mode\":" + cfg.set_mode + ",";
    message = message + "\"hour\":" + cfg.hour + ",";
    message = message + "\"minute\":" + cfg.minute;
    message += "}"; // End JSON

    _server.send(200, "application/json",  message);
}

void handle_set()
{
    if (_server.hasArg("plain") == false)
    { // Check if body received

        _server.send(200, "text/plain", "Body not received");
        return;
    }

    StaticJsonDocument<512> doc;

    DeserializationError error = deserializeJson(doc, _server.arg("plain"));

    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }

    String message = "";

    if (doc.containsKey("hour_speed"))
    {
        int hour_speed = doc["hour_speed"];
        message += "Set hour speed to: ";
        message += hour_speed;
        message += "\n";
        clock_manager.setHourSpeed(hour_speed);
    }
    if (doc.containsKey("minute_speed"))
    {
        int minute_speed = doc["minute_speed"];
        message += "Set minute speed to: ";
        message += minute_speed;
        message += "\n";
        clock_manager.setMinuteSpeed(minute_speed);
    }
    if (doc.containsKey("hour_accel"))
    {
        int hour_accel = doc["hour_accel"];
        message += "Set hour accel to: ";
        message += hour_accel;
        message += "\n";
        clock_manager.setHourAccel(hour_accel);
    }
    if (doc.containsKey("minute_accel"))
    {
        int minute_accel = doc["minute_accel"];
        message += "Set minute accel to: ";
        message += minute_accel;
        message += "\n";
        clock_manager.setMinuteAccel(minute_accel);
    }
    if (doc.containsKey("hour_dir"))
    {
        int hour_direction = doc["hour_dir"];
        message += "Set hour direction to: ";
        message += hour_direction;
        message += "\n";
        clock_manager.setHourDirection(hour_direction);
    }
    if (doc.containsKey("minute_dir"))
    {
        int minute_direction = doc["minute_dir"];
        message += "Set minute direction to: ";
        message += minute_direction;
        message += "\n";
        clock_manager.setMinuteDirection(minute_direction);
    }
    if (doc.containsKey("hour") && doc.containsKey("minute"))
    {
        int hour = doc["hour"]; // 04
        int minute = doc["minute"]; // 20
        message += "Set time to:\n";
        message += hour;
        message += ":";
        message += minute;
        message += "\n";
        clock_manager.setTime(hour, minute);        
    }
    if (doc.containsKey("mode"))
    {
        mode mode = doc["mode"];
        if (mode < CALM || mode > MANUAL) {
            message += "Invalid mode. Mode must be between 0 and 2\n";
        } else {
            message += "Set mode to: ";
            message += mode;
            message += "\n";
            clock_manager.setMode(mode);

            if (mode == MANUAL) {
                message += "Manual mode set. Sending full clocks\n";
                clock_manager.sendFullClocks();
            }
        }        
    }   
    
    _server.send(200, "text/plain", message);
}

void handle_get_time()
{
    StaticJsonDocument<256> doc;
    doc["time"] = now();

    String output;
    serializeJson(doc, output);
    _server.send(200, "application/json", output);
}