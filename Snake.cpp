#include "Snake.h"

void Snake::update()
{
    movePlayer();

    if (playerCrashed())
    {
        playing = false;
        finished = true;
    }

    if (playerAteFood())
    {
        spawnFood();
        grow();
    }

    if (movesUntilRespawn == 0)
    {
        spawnFood();
    }
}

void Snake::grow()
{
    player[length].value = TAIL;
    player[length].x = food.x;
    player[length].y = food.y;
    length++;

    // game becomes more difficult
    difficulty += DIFFICULTY_BIT;
}

bool Snake::playerAteFood()
{
    if ((player[0].x == food.x) && (player[0].y == food.y))
    {
        return true;
    }
    return false;
}

bool Snake::playerCrashed()
{
    for (int i = 1; i < length; i++)
    {
        if ((player[0].x == player[i].x) && (player[0].y == player[i].y))
        {
            return true;
        }
    }
    return false;
}

void Snake::sendInput(int towards)
{
    direction = towards % 4; // there are only 4 motions atm
}

void Snake::movePlayer()
{
    switch (direction)
    {
    case MOVE_RIGHT:
        moveParts(1, 0);
        break;
    case MOVE_LEFT:
        moveParts(-1, 0);
        break;
    case MOVE_UP:
        moveParts(0, -1);
        break;
    case MOVE_DOWN:
        moveParts(0, 1);
        break;
    }

    movesUntilRespawn -= 1;
}

void Snake::moveParts(int xAmount, int yAmount)
{
    int nextX = player[0].x;
    int nextY = player[0].y;
    int auxX;
    int auxY;

    // The board is cyclic,
    // meaning that if the player slides off one side
    // he will spawn the opposite side

    player[0].x = (player[0].x + xAmount) % BOARD_SIZE;
    player[0].x += (player[0].x < 0) ? BOARD_SIZE : 0;

    player[0].y = (player[0].y + yAmount) % BOARD_SIZE;
    player[0].y += (player[0].y < 0) ? BOARD_SIZE : 0;

    for (int i = 1; i < length; i++)
    {
        auxX = player[i].x;
        auxY = player[i].y;
        player[i].x = nextX;
        player[i].y = nextY;
        nextX = auxX;
        nextY = auxY;
    }
}

void Snake::render()
{
    drawPlayer();
    drawFood();
}

void Snake::drawFood()
{
    drawFoodPart(food.x, food.y);
}

void Snake::drawPlayer()
{
    for (int i = 0; i < length; i++)
    {
        drawSnakePart(player[i].x, player[i].y);
    }
}

void Snake::init()
{
    setupPlayer();
    spawnFood();
    playing = true;
    finished = false;
}

void Snake::spawnFood()
{
    bool ok = false;
    while (!ok)
    {
        food.x = generateRandomNumber();
        food.y = generateRandomNumber();
        if (food.x != player[0].x && food.y != player[0].y)
        {
            ok = true;
        }
    }

    if (difficulty > DIFFICULTY_THRESH)
    {
        // now food will respawn if the player doesn't eat it
        // in the least amount of moves

        int minx, maxx;
        int miny, maxy;

        // compute movesUntilRespawn

        if (player[0].x < food.x)
        {
            minx = player[0].x;
            maxx = food.x;
        }
        else
        {
            minx = food.x;
            maxx = player[0].x;
        }

        if (player[0].y < food.y)
        {
            miny = player[0].y;
            maxy = food.y;
        }
        else
        {
            miny = food.y;
            maxy = player[0].y;
        }

        movesUntilRespawn = (((maxx - minx) < (minx + BOARD_SIZE - maxx)) ? (maxx - minx) : (minx + BOARD_SIZE - maxx)) +
                            (((maxy - miny) < (miny + BOARD_SIZE - maxy)) ? (maxy - miny) : (miny + BOARD_SIZE - maxy));
    }
}

void Snake::setupPlayer()
{
    player[0].value = HEAD;
    player[0].x = 0;
    player[0].y = 0;

    for (int i = 1; i < BOARD_SIZE_SQRD; i++)
    {
        player[i].value = NEUTRAL;
        player[i].x = 0;
        player[i].y = 0;
    }
}

void Snake::over()
{
    gameOverDisplay();

    // reinit
    direction = -1;
    length = 1;
    difficulty = 0;
    finished = false;
}
