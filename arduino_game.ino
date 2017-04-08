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
  lc.setIntensity(0, 4); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);    // clear screen
}

/* Utility function for printing digits using lc */
void printDigit(int digit, int offset)
{
  int ox = 1 + (offset > 0 ? 3 : 0);
  int oy = 1;

  switch (digit)
  {
    case 0:
      lc.setLed(0, ox, oy, true);
      lc.setLed(0, ox, oy+1, true);
      lc.setLed(0, ox, oy+2, true);
      lc.setLed(0, ox, oy+3, true);
      lc.setLed(0, ox, oy+4, true);

      lc.setLed(0, ox+1, oy, true);
      lc.setLed(0, ox+1, oy+4, true);

      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+1, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+3, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

    case 1:
      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+1, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+3, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

    case 2:
      lc.setLed(0, ox, oy, true);
      lc.setLed(0, ox, oy+1, true);
      lc.setLed(0, ox, oy+2, true);
      lc.setLed(0, ox, oy+4, true);

      lc.setLed(0, ox+1, oy, true);
      lc.setLed(0, ox+1, oy+2, true);
      lc.setLed(0, ox+1, oy+4, true);

      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+3, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

    case 3:
      lc.setLed(0, ox, oy, true);
      lc.setLed(0, ox, oy+2, true);
      lc.setLed(0, ox, oy+4, true);

      lc.setLed(0, ox+1, oy, true);
      lc.setLed(0, ox+1, oy+2, true);
      lc.setLed(0, ox+1, oy+4, true);

      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+1, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+3, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

    case 4:
      lc.setLed(0, ox, oy+2, true);
      lc.setLed(0, ox, oy+3, true);
      lc.setLed(0, ox, oy+4, true);

      lc.setLed(0, ox+1, oy+2, true);

      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+1, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+3, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

    case 5:
      lc.setLed(0, ox, oy, true);
      lc.setLed(0, ox, oy+2, true);
      lc.setLed(0, ox, oy+3, true);
      lc.setLed(0, ox, oy+4, true);

      lc.setLed(0, ox+1, oy, true);
      lc.setLed(0, ox+1, oy+2, true);
      lc.setLed(0, ox+1, oy+4, true);

      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+1, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

    case 6:
      lc.setLed(0, ox, oy, true);
      lc.setLed(0, ox, oy+1, true);
      lc.setLed(0, ox, oy+2, true);
      lc.setLed(0, ox, oy+3, true);
      lc.setLed(0, ox, oy+4, true);

      lc.setLed(0, ox+1, oy, true);
      lc.setLed(0, ox+1, oy+2, true);
      lc.setLed(0, ox+1, oy+4, true);

      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+1, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

    case 7:
      lc.setLed(0, ox, oy+4, true);

      lc.setLed(0, ox+1, oy+4, true);

      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+1, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+3, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

    case 8:
      lc.setLed(0, ox, oy, true);
      lc.setLed(0, ox, oy+1, true);
      lc.setLed(0, ox, oy+2, true);
      lc.setLed(0, ox, oy+3, true);
      lc.setLed(0, ox, oy+4, true);

      lc.setLed(0, ox+1, oy, true);
      lc.setLed(0, ox+1, oy+2, true);
      lc.setLed(0, ox+1, oy+4, true);

      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+1, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+3, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

    case 9:
      lc.setLed(0, ox, oy, true);
      lc.setLed(0, ox, oy+2, true);
      lc.setLed(0, ox, oy+3, true);
      lc.setLed(0, ox, oy+4, true);

      lc.setLed(0, ox+1, oy, true);
      lc.setLed(0, ox+1, oy+2, true);
      lc.setLed(0, ox+1, oy+4, true);

      lc.setLed(0, ox+2, oy, true);
      lc.setLed(0, ox+2, oy+1, true);
      lc.setLed(0, ox+2, oy+2, true);
      lc.setLed(0, ox+2, oy+3, true);
      lc.setLed(0, ox+2, oy+4, true);
      break;

  }
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

  void delayBetweenUpdates(int difficulty)
  {
    delay(350 - difficulty);
  }

  void gameOverDisplay()
  {
    int score = getScore();

    lc.clearDisplay(0);

    // display game over animation
    
    for (int i = 0; i < 8; i++)
    {
      for (int j = 7; j >= 0; j--)
      {
        lc.setLed(0, j, i, true);
      }
      delay(150);
    }
    

    lc.clearDisplay(0);

    
    // display score

    printDigit(score / 10, 0);
    printDigit(score % 10, 1);


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

// this function restarts the game after receiving input
void awaitForInput() 
{
  x = analogRead(joystickX);
  y = analogRead(joystickY);
  
  if (x > UP_THRESH ||
      x < DOWN_THRESH ||
      y < RIGHT_THRESH ||
      y > LEFT_THRESH)
  {
    game.init();
  }
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
    game.delayBetweenUpdates(game.getDifficulty());
  } 
  else if (game.isFinished())
  {
    game.over();
    delay(250);
  } 
  else
  {
    awaitForInput();
    delay(150);
  }
}
