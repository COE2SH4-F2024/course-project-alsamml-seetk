#include "Food.h"
#include "MacUILib.h"
#include "GameMechs.h"
#include <iostream>

using namespace std;


Food::Food()
{
    //init food object to be outside gameboard 
    // so that before it is randomly placed it will not appear at (0,0) 
    foodPos.setObjPos(-10, -10, 'o');
}

Food::~Food()
{
    
}


void Food::generateFood(GameMechs* gameMechsPtr, objPos blockOff)
{
    //random food generation algorithm
    //blockoff the player position only 
    srand(static_cast<unsigned int>(time(0)));

    int boardWidth = gameMechsPtr->getBoardSizeX() - 2;
    int boardHeight = gameMechsPtr->getBoardSizeY() - 2;
    int xFood, yFood;

    do { 
        xFood = rand() % boardWidth + 1;
        yFood = rand() % boardHeight + 1;
    } while (xFood == blockOff.pos->x && yFood == blockOff.pos->y);

    
    foodPos.setObjPos(xFood, yFood,'o');
    // int count = ->getSize();
    // int randNum; 
    // int str_size = my_strlen(str);
    
    // int* xRandList = (int*)calloc(xRange, sizeof(int));
    // int* yRandList = (int*)calloc(yRange, sizeof(int)); 
    // int* charRandList = (int*)calloc(str_size, sizeof(int));

    // xRandList[player->x]++;
    // yRandList[player->y]++;

    // //generate non-repeating random x coord
    // do
    // {
    //     randNum = rand() % (xRange);

    //     if(randNum == 0 || randNum == (xRange - 1))
    //         continue;

    //     xRandList[randNum]++;
    //     count--;
    //     list[count].x = randNum;
    // } while (count > 0);

    // //generate non-repeating random y coord
    // count = listSize; 
    // do 
    // {
    //     randNum = rand() % (yRange);

    //     if(randNum == 0 || randNum == (yRange - 1))
    //         continue;

    //     yRandList[randNum]++;
    //     count--;
    //     list[count].y = randNum;
    // } while(count > 0);

    // //generate non-repeating random character choices 
    // do
    // {
    //     randNum = rand() % (str_size - 1);

    //     if(charRandList[randNum] != 0)
    //         continue;

    //     charRandList[randNum]++;
    //     count--;
    //     list[count].symbol = str[randNum];
    // } while(count > 0);
    
    // free(xRandList);
    // free(yRandList);
    // free(charRandList);
    
}


objPos Food::getFoodPos() const
{
    return foodPos;
}   