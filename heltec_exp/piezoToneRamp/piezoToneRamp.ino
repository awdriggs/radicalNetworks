// Define the pin connected to the piezo buzzer

#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"
#include <heltec_unofficial.h>

#define BUZZER_PIN 4
#define BUZZER_CHANNEL 0
int highFreq = 4000;

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

  /* for (int i = 0; i < 3; i++) { // Generate 3 short chirps */
  /*   tone(BUZZER_PIN, 4000, 100); // Play a tone at 4000 Hz for 100 ms */
  /*   delay(200);                  // Pause for 200 ms between chirps */
  /* } */

  /* delay(300); */

  for(int count = 0; count < 10; count++){
    //ramp up
    /* for (int freq = 0; freq <= highFreq; freq += 100) { // Increase frequency in steps of 100 Hz */
    /*   ledcWriteTone(BUZZER_PIN, freq); */
    /*   /1* display.println(String(freq)); *1/ */
    /*   delay(10);             // Wait 100 ms before the next frequency */
    /* } */

    //hold
    ledcWriteTone(BUZZER_PIN, highFreq);
    delay(100);

    /* //ramp down */
    /* for (int freq = highFreq; freq >= 0; freq -= 400) { // Increase frequency in steps of 100 Hz */

    /*   if(freq < 0){ */
    /*     freq = 0; //don't let it go neg */
    /*   } */

    /*   ledcWriteTone(BUZZER_PIN, freq); */

    /*   delay(20);             // Wait 100 ms before the next frequency */
    /* } */

    ledcWriteTone(BUZZER_PIN, 2000);
    // Wait for 1 second before toggling again
    delay(100); //silence


    display.display();
  }


  ledcWriteTone(BUZZER_PIN, 0);

  delay(280);
}
