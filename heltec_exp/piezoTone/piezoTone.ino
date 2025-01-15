// Define the pin connected to the piezo buzzer

#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"
#include <heltec_unofficial.h>

#define BUZZER_PIN 4
#define BUZZER_CHANNEL 0

// Variables to track the buzzer state
bool buzzerState = false;

void setup() {
  heltec_setup();

  // Set up the PWM channel
  ledcAttach(BUZZER_PIN, 1200, 8); // Attach pin 4 to channel 0
  /* ledcAttach(ledR, 12000, 8); */
  /* ledcSetup(0, 1000, 8);        // Channel 0, 1 kHz frequency, 8-bit resolution */
}

void loop() {
  display.cls();

  // Toggle the buzzer state
  buzzerState = !buzzerState;

  //display buzzer state
  if(buzzerState){
    display.println("on");
    Serial.println("on");

    // Generate a tone at 1 kHz
    /* ledcWrite(0, 128); // Set duty cycle to 50% (128 out of 255) */
    ledcWriteTone(BUZZER_PIN, 500);


  } else {
    display.println("off");
    Serial.println("off");
    // Turn the buzzer off
    ledcWriteTone(BUZZER_PIN, 0);
    ledcWrite(0, 0); // Set duty cycle to 0
  }

  // Wait for 1 second before toggling again
  delay(500);

  display.display();
}
