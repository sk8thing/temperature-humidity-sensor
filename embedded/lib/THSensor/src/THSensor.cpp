#include "THSensor.h"

THSensor::THSensor(
    int thermistorChargePin,
    int thermistorReadPin,
    int humidityPulsePin1,
    int humidityPulsePin2,
    int humidityReadPin
    ) {

    thermistorCharge = thermistorChargePin;
    thermistorRead = thermistorReadPin;
    humidityPulse1 = humidityPulsePin1;
    humidityPulse2 = humidityPulsePin2;
    humidityRead = humidityReadPin;
}

void THSensor::begin() {
    analogReadResolution(12);
    pinMode(thermistorRead, INPUT);
    pinMode(thermistorCharge, OUTPUT);
    digitalWrite(thermistorCharge, LOW);

    pinMode(humidityRead, INPUT);
    pinMode(humidityPulse1, OUTPUT);
    digitalWrite(humidityPulse1, LOW);
    pinMode(humidityPulse2, OUTPUT);
    digitalWrite(humidityPulse2, LOW);
}

unsigned int THSensor::readThermistor() {
    digitalWrite(thermistorCharge, HIGH);
    delay(100);

    unsigned int raw = analogRead(thermistorRead);
    digitalWrite(thermistorCharge, LOW);
    return raw;
}

float THSensor::readTemperature() {
    unsigned int read = readThermistor();
    double vout = (VIN / 4095.) * read;
    double r = (vout * R1) / (VIN - vout);
    double kelvin = 1 / (STEINHART_A + (STEINHART_B * log(r)) + (STEINHART_C * pow(log(r), 3)));
    auto celsius = static_cast<float>(kelvin - 273.15);
    temperature = celsius;
    return temperature;
}

unsigned int THSensor::temperatureToIndex(float temperature) {
    if(temperature >= 0 && temperature < 5) return 1;
    if(temperature >= 5 && temperature < 10) return 2;
    if(temperature >= 10 && temperature < 15) return 3;
    if(temperature >= 15 && temperature < 20) return 4;
    if(temperature >= 20 && temperature < 25) return 5;
    if(temperature >= 25 && temperature < 30) return 6;
    if(temperature >= 30 && temperature < 35) return 7;
    if(temperature >= 35 && temperature < 40) return 8;
    if(temperature >= 40 && temperature < 45) return 9;
    if(temperature >= 45 && temperature < 50) return 10;
    if(temperature >= 50 && temperature < 55) return 11;
    if(temperature >= 55 && temperature < 60) return 12;
    return 0;
}

unsigned int THSensor::readHR202() {
    digitalWrite(humidityPulse1, HIGH);
    digitalWrite(humidityPulse2, LOW);
    unsigned int raw = analogRead(humidityRead);
    digitalWrite(humidityPulse1, LOW);
    digitalWrite(humidityPulse2, HIGH);

    delayMicroseconds(109);
    digitalWrite(humidityPulse1, LOW);
    digitalWrite(humidityPulse2, LOW);

    return raw;
}

float THSensor::readHumidity() {
    if(millis() - lastReadTime > 5000) {
        const unsigned int index = temperatureToIndex(temperature);
        unsigned int read = readHR202();
        double vout = (VIN / 4095.) * read;
        double r = (vout * R1) / (VIN - vout);
        if(index == 0) humidity = static_cast<float>(regressionConstants[index] * pow(r, regressionExponents[index]));
        else {
            auto lower = static_cast<float>(regressionConstants[index - 1] * pow(r, regressionExponents[index - 1]));
            auto upper = static_cast<float>(regressionConstants[index] * pow(r, regressionExponents[index]));
            float weight = (float)(5 * index) - temperature;
            humidity = (lower * weight) + (upper * (5 - weight));
            humidity /= 5.0;
        }
        lastReadTime = millis();
        return humidity;

    } else return humidity;
}