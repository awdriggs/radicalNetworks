// Define the pin connected to the piezo buzzer

#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"
#include <heltec_unofficial.h>

#define BUZZER_PIN 4
#define BUZZER_CHANNEL 0
int highFreq = 8000;
int lowFreq = 4000;

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

  for(int count = 0; count < 5; count++){

    //ramp up
    for (int freq = lowFreq; freq <= highFreq; freq += 100) { // Increase frequency in steps of 100 Hz
      ledcWriteTone(BUZZER_PIN, freq);
      /* display.println(String(freq)); */
      delay(10);             // Wait 100 ms before the next frequency
    }

    //hold high freq
    ledcWriteTone(BUZZER_PIN, highFreq);
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

    display.display();
  }


  ledcWriteTone(BUZZER_PIN, 0);

  delay(280);
}
