#include "Food.h"
#include "MacUILib.h"
#include "GameMechs.h"
#include "objPos.h"
#include "Player.h"


Food::Food()
{
    //init food object to be outside gameboard 
    // so that before it is randomly placed it will not appear at (0,0) 
    foodPos.setObjPos(-10, -10, 'o');
}

Food::~Food()
{
    
}


void Food::generateFood(objPos blockOff)
{
    //random food generation algorithm
    //blockoff the player position only 
    int count = ->getSize();
    int randNum; 
    int str_size = my_strlen(str);
    
    int* xRandList = (int*)calloc(xRange, sizeof(int));
    int* yRandList = (int*)calloc(yRange, sizeof(int)); 
    int* charRandList = (int*)calloc(str_size, sizeof(int));

    xRandList[player->x]++;
    yRandList[player->y]++;

    //generate non-repeating random x coord
    do
    {
        randNum = rand() % (xRange);

        if(randNum == 0 || randNum == (xRange - 1))
            continue;

        xRandList[randNum]++;
        count--;
        list[count].x = randNum;
    } while (count > 0);

    //generate non-repeating random y coord
    count = listSize; 
    do 
    {
        randNum = rand() % (yRange);

        if(randNum == 0 || randNum == (yRange - 1))
            continue;

        yRandList[randNum]++;
        count--;
        list[count].y = randNum;
    } while(count > 0);

    //generate non-repeating random character choices 
    do
    {
        randNum = rand() % (str_size - 1);

        if(charRandList[randNum] != 0)
            continue;

        charRandList[randNum]++;
        count--;
        list[count].symbol = str[randNum];
    } while(count > 0);
    
    free(xRandList);
    free(yRandList);
    free(charRandList);
    
}


objPos Food::getFoodPos() const
{
    return foodPos;
}   