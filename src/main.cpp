#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>



// BLE Service and Characteristic UUIDs
#define SERVICE_UUID "12345678-1234-5678-1234-56789abcdef0"
#define CHARACTERISTIC_UUID "12345678-1234-5678-1234-56789abcdef1"
#define HALL_SENSOR_PIN 4
#define UPDATE_INTERVAL 1000
#define DEBOUNCE_US 1000




BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
bool deviceConnected = false;

// Global variables
volatile unsigned long pulseCount = 0;
volatile unsigned long lastPulseTime = 0;
unsigned long lastUpdateTime = 0;


void countPulse() {
    unsigned long currentTime = micros();
    if ((currentTime - lastPulseTime) > DEBOUNCE_US) {
        pulseCount++;
    }
    lastPulseTime = currentTime;
}

void initializeHallSensor() {
    pinMode(HALL_SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulse, FALLING);
  }

float getHz() {
    
    noInterrupts();
    unsigned long currentPulseCount = pulseCount;
    pulseCount = 0;
    interrupts();

    unsigned long elapsedTime = millis() - lastUpdateTime;
    return currentPulseCount * (1000.0 / elapsedTime);
  }


// Callback for BLE Server
class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    }

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
    }
};



void setup() {
    Serial.begin(115200);
    

    // Initialize BLE
    // BLEDevice::init("Jetblack Power Meter");
    // pServer = BLEDevice::createServer();
    // pServer->setCallbacks(new MyServerCallbacks());
    
    // BLEService *pService = pServer->createService(SERVICE_UUID);

    // pCharacteristic = pService->createCharacteristic(
    //     CHARACTERISTIC_UUID,
    //     BLECharacteristic::PROPERTY_NOTIFY
    // );
    // pService->start();
    
    // BLEAdvertising *pAdvertising = pServer->getAdvertising();
    // pAdvertising->start();
    
    // Serial.println("BLE Server is ready and advertising...");

    initializeHallSensor();
}



void loop() {
    // Read speed data from the hall-effect sensor
    unsigned long currentTime = millis();

    
  
    if (currentTime - lastUpdateTime >= UPDATE_INTERVAL) {
    float Hz = getHz();
      lastUpdateTime = currentTime;

      Serial.print("Freq: ");
      Serial.println(Hz);

          // Broadcast power meter data if a device is connected
        // if (deviceConnected) {
        //     pCharacteristic->setValue(rpm);
        //     pCharacteristic->notify();
        // }
    }

}