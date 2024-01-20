#ifndef EMBEDDED_THSENSOR_H
#define EMBEDDED_THSENSOR_H

#include <Arduino.h>
#include <Constants.h>

#define VIN 3.3
#define R1 10000
#define STEINHART_A (-0.0009500542517871515)
#define STEINHART_B 0.000589776210603468
#define STEINHART_C (-0.0000014276195692161472)

class THSensor {
    int thermistorCharge;
    int thermistorRead;
    int humidityPulse1;
    int humidityPulse2;
    int humidityRead;
    float temperature = 0.;
    float humidity = 0.;
    unsigned long int lastReadTime = 0;
    unsigned int readThermistor();
    unsigned int readHR202();
    unsigned int temperatureToIndex(float temperature);

public:
    THSensor(
        int thermistorChargePin,
        int thermistorReadPin,
        int humidityPulsePin1,
        int humidityPulsePin2,
        int humidityReadPin
    );
    void begin();
    float readTemperature();
    float readHumidity();

};


#endif //EMBEDDED_THSENSOR_H
