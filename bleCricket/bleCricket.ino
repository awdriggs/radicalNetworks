
// Turns the 'PRG' button into the power button, long press is off
#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"
#include <heltec_unofficial.h>

// load bluetooth bizness
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

//audio settings
#define BUZZER_PIN 4
int highFreq = 8000;
int lowFreq = 4000;

//ble setup
int scanTime = 5;  //In seconds
BLEScan *pBLEScan;

int totalRSSI = 0;
int deviceCount = 0;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {

    int rssi = advertisedDevice.getRSSI(); // Get the RSSI of the current device
    totalRSSI += rssi; // Add the RSSI to the total
    deviceCount++; // Increment the device count

    Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
  }
};


void setup() {
  heltec_setup();

  Serial.begin(115200);

  // Set up the PWM channel for piezo
  ledcAttach(BUZZER_PIN, 1200, 8); // Attach pin 4 to channel 0

  Serial.println("Scanning...");
  //reset signalAccum
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();  //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);  //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}


void loop() {
  totalRSSI = 0;   // Reset before each scan
  deviceCount = 0; // Reset before each scan

  // put your main code here, to run repeatedly:
  BLEScanResults *foundDevices = pBLEScan->start(scanTime, false);
  Serial.println("Scan done!");

  /* Serial.println(foundDevices->getCount()); */
  /* displayCount(foundDevices->getCount()); */

  if (deviceCount > 0) {
    Serial.print("Devices found: ");
    Serial.println(deviceCount);
    Serial.print("Total RSSI: ");
    Serial.println(totalRSSI);

    chirp(); //make a sound

  } else {
    Serial.println("No devices found. Skipping chirp.");
  }

  pBLEScan->clearResults();  // delete results fromBLEScan buffer to release memory
  delay(2000);
}


void chirp(){
  if (deviceCount == 0) return; // Safety check

  int rssiAvg = totalRSSI / deviceCount; //calc from scan totals

  Serial.print("rssiAvg: ");
  Serial.println(rssiAvg);

  int chirpFreq = map(rssiAvg, -90, 0, lowFreq, highFreq);

  Serial.print("chirp freq: ");
  Serial.println(chirpFreq);

  for(int count = 0; count < deviceCount/10; count++){

    //ramp up
    for (int freq = lowFreq; freq <= chirpFreq; freq += 100) { // Increase frequency in steps of 100 Hz
      ledcWriteTone(BUZZER_PIN, freq);
      /* display.println(String(freq)); */
      delay(10);             // Wait 100 ms before the next frequency
    }

    //hold high freq
    ledcWriteTone(BUZZER_PIN, chirpFreq);
    delay(50);

    //ramp down?
    /* for (int freq = highFreq; freq >= lowFreq; freq -= 100) { // Increase frequency in steps of 100 Hz */
    /*   if(freq < lowFreq){ //don't drop below the low! */
    /*     freq = lowFreq; */
    /*   } */

    /*   ledcWriteTone(BUZZER_PIN, freq); */
    /*   /1* display.println(String(freq)); *1/ */
    /*   delay(10);             // Wait 100 ms before the next frequency */
    /* } */

    //hold low freq
    ledcWriteTone(BUZZER_PIN, lowFreq);
    delay(50); //

    /* display.display(); */
  }


  ledcWriteTone(BUZZER_PIN, 0);

  /* delay(280); */
}
