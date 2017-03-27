// 8x8 led matrix snake game

#include "Snake.h"
#include "LedControl.h"

/* Led Matrix Setup */

LedControl lc = LedControl(12, 11, 10, 1);
// LedControl(int dataPin, int clkPin, int csPin, int numDevices=1)

void setupLedControl()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 8); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);    // clear screen
}

/* Game Class Setup */

class Game : public Snake
{
public:
  int generateRandomNumber()
  {
    return random(8);
  }

  int drawSnakePart(int x, int y)
  {
    lc.setLed(0, x, y, true);
  }

  int drawFoodPart(int x, int y)
  {
    lc.setLed(0, x, y, true);
  }

  void delayBetweenUpdates()
  {
    delay(350);
  }
} game;

/* Joystick Setup */

const int joystickX = 2;
const int joystickY = 1;
int x;
int y;

// these will serve as thresholds for left, right, up and down motions
const int LEFT_THRESH = 600;
const int RIGHT_THRESH = 400;
const int UP_THRESH = 600;
const int DOWN_THRESH = 400;

// the following 4 functions will trigger if their threshold is passed

void checkLeftMotion()
{
  if (y > LEFT_THRESH)
  {
    game.sendInput(game.MOVE_LEFT);
  }
}

void checkRightMotion()
{
  if (y < RIGHT_THRESH)
  {
    game.sendInput(game.MOVE_RIGHT);
  }
}

void checkUpMotion()
{
  if (x > UP_THRESH)
  {
    game.sendInput(game.MOVE_UP);
  }
}

void checkDownMotion()
{
  if (x < DOWN_THRESH)
  {
    game.sendInput(game.MOVE_DOWN);
  }
}

// this function wraps up the four above for clearer code
void handleInput()
{
  x = analogRead(joystickX);
  y = analogRead(joystickY);

  checkLeftMotion();
  checkRightMotion();
  checkUpMotion();
  checkDownMotion();
}

/* Arduino code */

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  setupLedControl();
  game.init();
}

void loop()
{
  if (game.isPlaying())
  {
    handleInput(); 
    lc.clearDisplay(0);
    game.render();
    game.update();
    game.delayBetweenUpdates();
  }
}
