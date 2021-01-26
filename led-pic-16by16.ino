#include "FastLED.h"
#include <IRremote.h>
#include "ControllerSetup.h"

//Setup for LED Strip
#define NUM_LEDS 256

CRGB leds[NUM_LEDS];
CRGB image[NUM_LEDS];
CRGB black = CRGB::Black;
CRGB colorSelection = CRGB::GhostWhite;

short fadeRatio = 51;
short maxFadeValue = 204; 
short minFadeValue = 51;
short currentFade = minFadeValue;

//Setup for InfraRed Remote
IRrecv irrecv(3);

void setup() { 
  FastLED.addLeds<WS2812B, 6, GRB>(leds, NUM_LEDS);
  irrecv.enableIRIn();
}

void loop() {

  //Wait for a remote command before checking all the controller logic
  if (irrecv.decode()) {
    switch(irrecv.results.value) {
      case upArrow: 
        oxControllerMoveUp();
        break;
       case downArrow:
        oxControllerMoveDown();
        break;
       case leftArrow:
        oxControllerMoveLeft();
        break;
       case rightArrow:
        oxControllerMoveRight();
        break;
       case toggleMode:
        controllerToggleMode();
        if ( currentMode == edit) {
          colorSelection = CRGB::GhostWhite;
        }
        break;
       case okayButton:
        setColor();
        colorSelection = CRGB::GhostWhite;
        break;
       default:
       pickColor(irrecv.results.value);
       break;
    }
    
    irrecv.resume();
  }
  
  renderImage(colorSelection);
  FastLED.show();
  delay(100);
}

void renderImage(CRGB color) {
  for(int idx = 0; idx < NUM_LEDS; idx++) {
    if (idx == selection - 1 && currentMode == edit) {
      leds[idx] = color == black ? CRGB::GhostWhite : color;
      leds[idx].fadeLightBy(currentFade);
    } else {
      leds[idx] = image[idx];
    }
  }

  currentFade += fadeRatio;
 
  if(currentFade <= minFadeValue || currentFade >= maxFadeValue){
    fadeRatio = -fadeRatio;
  }
}

void pickColor(int colorId){
  switch(colorId){
    case num0:
    colorSelection = CRGB::Black;
    break;
    case num1:
    colorSelection = CRGB::Maroon;
    break;
    case num2:
    colorSelection = CRGB::LawnGreen;
    break;
    case num3:
    colorSelection = CRGB::DarkBlue;
    break;
    case num4:
    colorSelection = CRGB::SkyBlue;
    break;
    case num5:
    colorSelection = CRGB::DarkViolet;
    break;
    case num6:
    colorSelection = CRGB::OrangeRed;
    break;
    case num7:
    colorSelection = CRGB::Salmon;
    break;
    case num8:
    colorSelection = CRGB::Yellow;
    break;
    case num9:
    colorSelection = CRGB::NavajoWhite;
    break;
  }
}

void setColor(){
  image[selection-1] = colorSelection;
}
