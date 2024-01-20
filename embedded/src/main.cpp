#include <Arduino.h>
#include <THSensor.h>
#include <WirelessComm.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define ADC2 28
#define ADC0 26
#define CHARGE 22
#define ADC1 27
#define PULSE1 14
#define PULSE2 15
#define SSID "exampleAP"
#define PSK "examplePSK"
#define API "https://example.com/sensor"
#define API_KEY "exampleAPIKEY"

WirelessComm comm(SSID, PSK, API, API_KEY);
THSensor sensor(CHARGE, ADC0, PULSE1, PULSE2, ADC1);
DHT dht(ADC2, DHT11);

void setup1() {
    comm.begin();
}

void setup() {
    Serial.begin(9600);

    sensor.begin();
    pinMode(ADC2, INPUT);
    dht.begin();
}

void loop() {
    float celsius = sensor.readTemperature();
    float humidity = sensor.readHumidity();
    if(WiFi.connected()) comm.update(celsius, humidity);
    Serial.print("Temperature: ");
    Serial.print(celsius);
    Serial.print(" Humidity: ");
    Serial.println(humidity);
    Serial.print("DHT11 temperature: ");
    Serial.println(dht.readTemperature());
    Serial.print("DHT11 humidity: ");
    Serial.println(dht.readHumidity());
    delay(900);
}