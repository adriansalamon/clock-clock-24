#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <WebServer.h>
#include "clock_manager.h"

class ClockWebServer
{

private:
    ClockManager *_clock_manager;

public:
    ClockWebServer();

    void begin(ClockManager *clock_manager);
    void update();
};

void handle_get();
void handle_set();
void handle_get_time();

#endif // WEB_SERVER_H