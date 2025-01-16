
#include <heltec_unofficial.h>


#define CENTER_X 64
#define CENTER_Y 32

int size = 100;

void setup() {
  heltec_setup();
  Serial.println("display experiment");

  // Initialising the UI will init the display too.
  display.init();

  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 26, "Hello!");
  delay(2000);
}

void drawRect(int size) {
  //draw a rect from the center out

  /* // Draw a pixel at given position */
  /* for (int i = 0; i < 10; i++) { */
  /*   display.setPixel(i, i); */
  /*   display.setPixel(10 - i, i); */
  /* } */

  /* display.drawRect(CENTER_X - size/2, 0, CENTER_X + size/2, 64); */
  display.drawRect(CENTER_X - size / 2, 0, size, 64);
  display.fillRect(CENTER_X - size / 2, 0, size, 64);
}

//keeping for the future
/* void drawCircleDemo() { */
/*   for (int i = 1; i < 8; i++) { */
/*     display.setColor(WHITE); */
/*     display.drawCircle(32, 32, i * 3); */
/*     if (i % 2 == 0) { */
/*       display.setColor(BLACK); */
/*     } */
/*     display.fillCircle(96, 32, 32 - i * 3); */
/*   } */
/* } */

void loop() {
  heltec_loop();
  // clear the display
  display.clear();


  drawRect(size); 
  
  size += 10; //increase the size of the rect
  if(size > 128){ //for next loop, check to see if it is larger than the screen width
    size=10;
  }

  //into on bottom, could be used for debuggin in the future
  /* display.setFont(ArialMT_Plain_10); */
  /* display.setTextAlignment(TEXT_ALIGN_RIGHT); */
  /* display.drawString(128, 54, String(millis())); */
  // write the buffer to the display

  display.display();

  delay(100);
}

