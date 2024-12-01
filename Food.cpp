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
Food::Food(const Food &f){
    foodPos = f.foodPos;
   


}
Food& Food::operator=(const Food &f){
    if (this != &f){
        foodPos = f.foodPos;
    }
    return *this;
}
void Food::generateFood(GameMechs* gameMechsPtr, objPosArrayList* blockOff)
{
    //random food generation algorithm
    //blockoff the player position only 
    srand(static_cast<unsigned int>(time(0)));

    int boardWidth = gameMechsPtr->getBoardSizeX() - 2;
    int boardHeight = gameMechsPtr->getBoardSizeY() - 2;
    int xFood, yFood;
    int flag = 0;

    do { 
        flag = 1;
        xFood = rand() % boardWidth + 1;
        yFood = rand() % boardHeight + 1;

        //check if generated pos matches any blocked positions 
        for(int i = 0; i < blockOff->getSize(); i++) { 
            objPos currentBlock = blockOff->getElement(i);
            if(xFood == currentBlock.pos->x && yFood == currentBlock.pos->y) { 
                flag = 0;
                break;
            }
        }
    } while (flag == 0);

    
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