#include "WirelessComm.h"

WirelessComm::WirelessComm(const char *ssid, const char *psk, const char *api_url, const char *api_key) {
    this->ssid = ssid;
    this->psk = psk;
    this->api_url = api_url;
    this->api_key = api_key;
}

void WirelessComm::begin() {
    do {
        WiFi.begin(ssid, psk);
        delay(1000);
        if(!WiFi.connected()) Serial.println("Cannot connect to WiFi");
    } while(!WiFi.connected());
    Serial.println("Successfully connected to WiFi!");
    https.setInsecure();
    https.begin(api_url);
    Serial.println("Successfully connected to API!");
}

void WirelessComm::update(float temperature, float humidity) {
    if(!WiFi.isConnected()) begin();
    char payload[128];
    sprintf(payload, JSON_DATA, api_key, temperature, humidity);
    https.addHeader("Content-Type", "application/json");
    https.POST(payload);
}
