// Define the pin connected to the piezo buzzer

#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"
#include <heltec_unofficial.h>

#define BUZZER_PIN 4
#define BUZZER_CHANNEL 0

// Variables to track the buzzer state
bool buzzerState = false;

const uint8_t* font = ArialMT_Plain_24;

void setup() {
  heltec_setup();

  // Set up the PWM channel
  ledcAttach(BUZZER_PIN, 1200, 8); // Attach pin 4 to channel 0
  /* ledcAttach(ledR, 12000, 8); */
  /* ledcSetup(0, 1000, 8);        // Channel 0, 1 kHz frequency, 8-bit resolution */
}

void loop() {
  display.cls();

  //Note test
  /* ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL); */
  ledcWriteNote(BUZZER_PIN, NOTE_C, 4);
  display.setFont(font);
  display.println("C");
  delay(500);
  ledcWriteNote(BUZZER_PIN, NOTE_D, 4);
  display.println("D");
  delay(500);
  ledcWriteNote(BUZZER_PIN, NOTE_E, 4);
  display.println("E");
  delay(500);
  ledcWriteNote(BUZZER_PIN, NOTE_F, 4);
  display.println("F");
  delay(500);
  ledcWriteNote(BUZZER_PIN, NOTE_G, 4);
  display.println("G");
  delay(500);
  ledcWriteNote(BUZZER_PIN, NOTE_A, 4);
  display.println("F");
  delay(500);
  ledcWriteNote(BUZZER_PIN, NOTE_B, 4);
  display.println("B");
  delay(500);
  /* ledcDetach(BUZZER_PIN); */

  display.display();
}
