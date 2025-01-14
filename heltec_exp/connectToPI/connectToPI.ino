#include <WiFi.h>

#define CONNECTION_TIMEOUT 10

// const char* ssid = "awd";
// const char* password = "Qed4scbv";
const char* ssid = "awdpi";
// const char* password = "AdamIsYourHost";
// const char* ssid = "RadicalNetworks2025";
// const char* password = "R@dicalNetworks";

void setup(){
    Serial.begin(115200);
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

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop(){}
