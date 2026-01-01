/*
 * LCD test 2.c
 *
 * Created: 3/14/2018 3:46:31 PM
 * Author : Tommy
 *
 * This code is from https://github.com/tshiels/Snake/blob/master/main.c
 * Edditted by Bora and Orhun
 */
#pragma once
#include <stdlib.h>
#include "Utils.h"
#include <stdbool.h>

bool IsThereSelfCollision(Point *snake, const int snakeLength)
{
    for (int i = 1; i < snakeLength; ++i)
    {
        if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y))
        {
            return true;
        }
    }
    return false;
}
// Return:
// Nothing -> 0
// Collision -> 1
// Eat Apple -> 2
int MoveSnake(const int direction, Point *snake, int *snakeLengthPtr, const Point Apple)
{
    bool edgeCollision = false;
    Point oldHead = snake[0];

    // shift all points down one, starting with the head at snake[0]
    for (int i = *snakeLengthPtr; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    if (direction == 0) // up
    {
        oldHead.y > 0 ? snake[0].y -= 1 : (edgeCollision = true);
    }
    else if (direction == 2) // down
    {
        oldHead.y < GAME_GRID_Y - 1 ? snake[0].y += 1 : (edgeCollision = true);
    }
    else if (direction == 1) // right
    {
        oldHead.x < GAME_GRID_X - 1 ? snake[0].x += 1 : (edgeCollision = true);
    }
    else if (direction == 3) // left
    {
        oldHead.x > 0 ? snake[0].x -= 1 : (edgeCollision = true);
    }

    if (snake[0].x == Apple.x && snake[0].y == Apple.y)
    {
        (*snakeLengthPtr)++;
        return 2;
    }

    int collision = edgeCollision || IsThereSelfCollision(snake, *snakeLengthPtr);
    return collision;
}

void ResetApple(Point *ApplePtr, Point *Snake, int snakeLength)
{
    bool collisionDetected;
    do
    {
        collisionDetected = false;
        // Generate random coordinates
        ApplePtr->x = (rand() % GAME_GRID_X);
        ApplePtr->y = (rand() % GAME_GRID_Y);

        // Check if collision with snake
        for (int i = 0; i < snakeLength; i++)
        {
            if (ApplePtr->x == Snake[i].x && ApplePtr->y == Snake[i].y)
            {
                collisionDetected = true;
                break;
            }
        }
    } while (collisionDetected);
}
