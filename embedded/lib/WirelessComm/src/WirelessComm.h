#ifndef EMBEDDED_WIRELESSCOMM_H
#define EMBEDDED_WIRELESSCOMM_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define JSON_DATA "{\"api_key\":\"%s\", \"temperature\":%.2f, \"humidity\":%.2f}"

class WirelessComm {
    const char *ssid;
    const char *psk;
    const char *api_url;
    const char *api_key;
    HTTPClient https;
public:
    WirelessComm(const char *ssid, const char *psk, const char *api_url, const char *api_key);
    void begin();
    void update(float temperature, float humidity);
};


#endif //EMBEDDED_WIRELESSCOMM_H
