// Turns the 'PRG' button into the power button, long press is off
#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"
/* #include <heltec_unofficial.h> */

#include <Wire.h>
#include "HT_SSD1306Wire.h"

// load bluetooth bizness
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

//Display
//for the two new boards
static SSD1306Wire  display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst
#define CENTER_X 64
#define CENTER_Y 32

int size = 100;

//audio settings
#define BUZZER_PIN 4
int highFreq = 8000;
int lowFreq = 4000;

//ble setup
int scanTime = 5;  //In seconds
BLEScan *pBLEScan;
int scanningRSSI = 0;
int scanningDeviceCount = 0;
bool scanInProgress = false;

// Timing variables
/* unsigned long lastChirpTime = 0; */
/* unsigned long chirpInterval = 100; // Interval between chirps (ms) */

//updated at the end of the scan
int totalRSSI = 0;
int deviceCount = 0;

int rssiAvg = 0;
int chirpFreq = 0;

//class definiation for each scan result callback
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {

    int rssi = advertisedDevice.getRSSI(); // Get the RSSI of the current device
    scanningRSSI += rssi; // Add the RSSI to the total
    scanningDeviceCount++; // Increment the device count
    /* Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str()); */
  }
};

void setup() {
  /* heltec_setup(); */

  VextON();
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

    // Initialising the UI will init the display too.
  display.init();

  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 26, "BLuE Cricket");
  delay(2000);

}

void loop() {
  /* heltec_loop(); //needed? */
  /* display.clear(); */

  if(!scanInProgress){
    pBLEScan->clearResults();  // delete old results fromBLEScan buffer to release memory

    //reset scanvariables
    scanningRSSI = 0;
    scanningDeviceCount = 0;

    pBLEScan->start(5, scanCompleteCallback);
    scanInProgress = true;
    Serial.println("BLE scan started...");
  }

  if (deviceCount > 0) {
    chirp(); //make a sound

  } else {
    Serial.println("No devices found. Skipping chirp.");
  }

  /* display.display(); //how often do you need to call this? */
  delay(280); //delay between chirps
}

void chirp(){
  if (deviceCount == 0) return; // Safety check

  rssiAvg = totalRSSI / deviceCount; //calc from scan totals

  Serial.print("rssiAvg: ");
  Serial.println(rssiAvg);

  chirpFreq = map(rssiAvg, -100, -20, lowFreq, highFreq); //tune, most averages in the the high 80s to low 90s

  Serial.print("chirp freq: ");
  Serial.println(chirpFreq);
  int size;

  for(int count = 0; count < deviceCount/10; count++){
    //ramp up
    for (int freq = lowFreq; freq <= chirpFreq; freq += 100) { // Increase frequency in steps of 100 Hz
      size = map(freq, lowFreq, highFreq, 10, 128);
      ledcWriteTone(BUZZER_PIN, freq);
      /* display.println(String(freq)); */
      drawRect(size);
      display.display();
      delay(10);             // Wait 100 ms before the next frequency
    }

    //hold high freq
    ledcWriteTone(BUZZER_PIN, chirpFreq);

    delay(100);

    //ramp down?
    /* for (int freq = highFreq; freq >= lowFreq; freq -= 100) { // Increase frequency in steps of 100 Hz */
    /*   if(freq < lowFreq){ //don't drop below the low! */
    /*     freq = lowFreq; */
    /*   } */

    /*   ledcWriteTone(BUZZER_PIN, freq); */
    /*   /1* display.println(String(freq)); *1/ */
    /*   delay(10);             // Wait 100 ms before the next frequency */
    /* } */

    display.clear();
    drawRect(0);
    display.display();
    //hold low freq
    ledcWriteTone(BUZZER_PIN, lowFreq);
    delay(100); //

    /* display.display(); */
  }

    //ramp down?
    /* for (int freq = lowFreq; freq >= 0; freq -= 100) { // Increase frequency in steps of 100 Hz */
    /*   if(freq < 0){ //don't drop below the low! */
    /*     freq = 0; */
    /*   } */

    /*   ledcWriteTone(BUZZER_PIN, freq); */
    /*   /1* display.println(String(freq)); *1/ */
    /*   delay(1);             // Wait 100 ms before the next frequency */
    /* } */

  /* drawRect(1); */
  /* display.display(); */
  display.clear();
  ledcWriteTone(BUZZER_PIN, 0);

  /* delay(280); */
}

// Called when the BLE scan is complete
void scanCompleteCallback(BLEScanResults results) {
  Serial.println("BLE scan complete!");
  deviceCount = scanningDeviceCount;
  totalRSSI = scanningRSSI;

  if (scanningDeviceCount > 0) {
    Serial.printf("Devices found: %d\n", deviceCount);
    Serial.printf("Total RSSI: %d\n", totalRSSI);
  } else {
    Serial.println("No devices found.");
  }

  scanInProgress = false; // Allow the next scan to start
}

void drawRect(int size) {
  //draw a rect from the center out

  /* // Draw a pixel at given position */
  /* for (int i = 0; i < 10; i++) { */
  /*   display.setPixel(i, i); */
  /*   display.setPixel(10 - i, i); */
  /* } */

  /* display.drawRect(CENTER_X - size / 2, 0, size, 64); */
  display.fillRect(CENTER_X - size / 2, 0, size, 64);
}

void VextON(void)
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, LOW);
}
