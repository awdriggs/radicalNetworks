/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
   */

// Turns the 'PRG' button into the power button, long press is off
#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"

// creates 'radio', 'display' and 'button' instances
/* #include "/Users/awdriggs/code/arduino/libraries/Heltec_ESP32_LoRa_v3/src/heltec_unofficial.h" */
#include <heltec_unofficial.h>

// load bluetooth bizness
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5;  //In seconds
BLEScan *pBLEScan;

const uint8_t* font = ArialMT_Plain_24;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
  }
};

void setup() {
  heltec_setup();

  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();  //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);  //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults *foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices->getCount());
  displayCount(foundDevices->getCount());
  // displayCount(count);
  Serial.println("Scan done!");
  pBLEScan->clearResults();  // delete results fromBLEScan buffer to release memory
  delay(2000);
}

void displayCount(int count) {

  // clear the scan plot rectangle
  /* display.setColor(BLACK); */
  /* display.fillRect(0,0,STEPS, HEIGHT); */
  /* display.setColor(WHITE); */
  display.cls();
  display.setFont(font);
  String countStr = String(count);
  display.println(countStr);
  display.display();
}


