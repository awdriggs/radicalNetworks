//esp32 heltec
#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"

#include <heltec_unofficial.h>

// load bluetooth bizness
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

//wifi stuff
#include <WiFi.h>
#define CONNECTION_TIMEOUT 10
const char* ssid = "awdpi";
// const char* password = "AdamIsYourHost";

int scanTime = 5;  //In seconds
BLEScan *pBLEScan;

const uint8_t* largeFont = ArialMT_Plain_24;
const uint8_t* smallFont = ArialMT_Plain_16;

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

  delay(1000);

  WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  WiFi.begin(ssid);

  Serial.println("\nConnecting");
  int timeout_counter = 0;

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    // Print Wi-Fi status codes
    Serial.print(" Wi-Fi Status: ");
    switch (WiFi.status()) {
      case WL_IDLE_STATUS:
        Serial.println("Idle");
        break;
      case WL_NO_SSID_AVAIL:
        Serial.println("No SSID Available");
        break;
      case WL_SCAN_COMPLETED:
        Serial.println("Scan Completed");
        break;
      case WL_CONNECT_FAILED:
        Serial.println("Connection Failed");
        break;
      case WL_CONNECTION_LOST:
        Serial.println("Connection Lost");
        break;
      case WL_DISCONNECTED:
        Serial.println("Disconnected");
        break;
      default:
        Serial.println("Unknown Status");
        break;
    }

    delay(200);
    timeout_counter++;
    if(timeout_counter >= CONNECTION_TIMEOUT*5){
      ESP.restart();
    }
  }

  //if you get here you have a connection
  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
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
  display.setFont(smallFont);
  String countStr = String(count);
  display.println(countStr);

  /* display.println( */
  display.println(WiFi.localIP());
  display.println(String(WiFi.RSSI()));
  /* display.printf("  SNR: %.2f dB\n", radio.getSNR()); */

  
  /* display.setFont(smallFont); */
  /* display.println(String(WiFi.localIP())); */
  /* display.println(String(WiFi.RSSI())); */
  display.display();
  


}


