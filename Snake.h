struct Player
{
    int value;
    int x;
    int y;
};

struct Food
{
    int x;
    int y;
};

class Snake
{
  public:
    static const int BOARD_SIZE = 8;
    static const int BOARD_SIZE_SQRD = BOARD_SIZE * BOARD_SIZE;

    static const int NEUTRAL = 0;
    static const int HEAD = 1;
    static const int TAIL = 2;
    static const int FOOD = 8;

    static const int MOVE_RIGHT = 0;
    static const int MOVE_LEFT = 1;
    static const int MOVE_UP = 2;
    static const int MOVE_DOWN = 3;

    static const int DIFFICULTY_BIT = 5;
    static const int DIFFICULTY_THRESH = 5 * DIFFICULTY_BIT;

    // INPUT
    // direction should be one of the MOVE_ variables
    void sendInput(int direction);

    // game state functions
    void init();
    void update();
    void render();
    void over();
    bool isPlaying() { return playing; }
    bool isFinished() { return finished; }

    // getter for difficulty
    int getDifficulty() { return difficulty; }

    // getter for score
    int getScore() { return length; }

    // handler for generating random positions
    virtual int generateRandomNumber() = 0;

    // handler for drawing each part of the snake
    virtual int drawSnakePart(int x, int y) = 0;

    // handler for drawing food
    virtual int drawFoodPart(int x, int y) = 0;

    // handler for delay between updates
    virtual void delayBetweenUpdates(int difficulty = 0) = 0;

    // handler for end game
    virtual void gameOverDisplay() = 0;

  private:
    // game variables
    bool playing;
    bool finished;
    int difficulty = 0;

    // food variables
    Food food;
    int movesUntilRespawn = -1;

    // player variables
    Player player[BOARD_SIZE_SQRD];
    int direction = -1; // it doesn't move on start
    int length = 1;

    // init functions
    void setupPlayer();
    void spawnFood();

    //update functions
    void movePlayer();
    void moveParts(int xAmount, int yAmount);
    bool playerCrashed();
    bool playerAteFood();
    void grow();

    // render functions
    void drawFood();
    void drawPlayer();
};
