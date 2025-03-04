#ifndef HALL_EFFECT_SENSOR_H
#define HALL_EFFECT_SENSOR_H

#include <Arduino.h>

class HallEffectSensor {
public:
    HallEffectSensor(int pin);
    void begin();
    float readSpeed();

private:
    int sensorPin;
    volatile unsigned long pulseCount;
    unsigned long lastTime;
    void countPulse();
};

#endif // HALL_EFFECT_SENSOR_H