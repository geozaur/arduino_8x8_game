#include "Snake.h"

void Snake::update()
{
    movePlayer();

    if (playerCrashed())
    {
        playing = false;
    }

    if (playerAteFood())
    {
        grow();
        spawnFood();
    }
}

void Snake::grow()
{
    player[length].value = TAIL;
    player[length].x = food.x;
    player[length].y = food.y;
    length++;
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
}

void Snake::spawnFood()
{
    bool ok = false;
    while (!ok) 
    {
        food.x = generateRandomNumber();
        food.y = generateRandomNumber();
        if (food.x != player.x && food.y != player.y)
        {
            ok = true;
        }
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