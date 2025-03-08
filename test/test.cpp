#include <Arduino.h>

void setup() {
    // Initialize serial communication at 115200 baud rate
    Serial.begin(115200);
    while (!Serial) {
        ; // Wait for serial port to connect. Needed for native USB
    }
    Serial.println("ESP32-S2 USB Serial Test");
}

void loop() {
    // Print a message every second
    Serial.println("Hello, world!");
    delay(1000);
}