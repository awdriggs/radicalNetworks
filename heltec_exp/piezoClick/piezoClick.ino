// Define the pin connected to the piezo buzzer

#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"
#include <heltec_unofficial.h>

#define BUZZER_PIN 4

// Variables to track the buzzer state
bool buzzerState = false;

void setup() {
  heltec_setup();
  // Initialize the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);

  // Start with the buzzer off
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Toggle the buzzer state
  buzzerState = !buzzerState;

  //display buzzer state
  display.cls();
  if(buzzerState){
    display.println("on");
    Serial.println("on");
  } else {
    display.println("off");
    Serial.println("off");
  }
  display.display();

  // Update the buzzer pin
  digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);

  // Wait for 1 second before toggling again
  delay(1000);
}

