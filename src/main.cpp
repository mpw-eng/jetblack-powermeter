#include <Arduino.h>

#define HALL_SENSOR_PIN 4
#define UPDATE_INTERVAL 1000000  // update interval (us)
#define DEBOUNCE_US 1000  // debounce time (us)


// Global variables
volatile unsigned long pulseCount = 0;
volatile unsigned long lastPulseTime = 0;
volatile unsigned long accumPulseTime = 0;
unsigned long lastUpdateTime = 0;


void countPulse() {
    unsigned long currentTime = micros();
    unsigned long elapsedTime = currentTime - lastPulseTime;
    if ((elapsedTime > DEBOUNCE_US) && (elapsedTime < 100000000)) {
        pulseCount++;
        accumPulseTime += elapsedTime;
    }
    lastPulseTime = currentTime;
}

void initializeHallSensor() {
    pinMode(HALL_SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulse, FALLING);
}


void setup() {
    Serial.begin(115200);

    initializeHallSensor();
}

void loop() {
    // Read speed data from the hall-effect sensor
    unsigned long currentTime = micros();

    if (currentTime - lastUpdateTime >= UPDATE_INTERVAL) {
        float Hz = 0;

        // Read interrupt pulse count & reset
        noInterrupts();
        unsigned long currentPulseCount = pulseCount;
        unsigned long currentAccumPulseTime = accumPulseTime;
        pulseCount = 0;
        accumPulseTime = 0;
        interrupts();
        
        // Calculate frequency
        //unsigned long elapsedTime = currentTime - lastUpdateTime;
        //float Hz = currentPulseCount * (1000000.0 / elapsedTime);
        if (currentPulseCount > 0){
            Hz = currentPulseCount * (1000000.0 / currentAccumPulseTime);
        } 
        
        lastUpdateTime = currentTime;
        
        Serial.print("Freq: ");
        Serial.println(Hz);

    }

}