#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>



// BLE Service and Characteristic UUIDs
#define SERVICE_UUID "12345678-1234-5678-1234-56789abcdef0"
#define CHARACTERISTIC_UUID "12345678-1234-5678-1234-56789abcdef1"
#define HALL_SENSOR_PIN 4
#define UPDATE_INTERVAL 1000000  // update interval (us)
#define DEBOUNCE_US 1000  // debounce time (us)




BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
bool deviceConnected = false;

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

          // Broadcast power meter data if a device is connected
        // if (deviceConnected) {
        //     pCharacteristic->setValue(rpm);
        //     pCharacteristic->notify();
        // }
    }

}