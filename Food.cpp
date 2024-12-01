#include "Food.h"
#include <cstdlib>
#include <time.h>
#include "objPos.h"

using namespace std;


Food::Food()
{
    //init food object to be outside gameboard 
    // so that before it is randomly placed it will not appear at (0,0) 
    //foodPos.setObjPos(-10, -10, 'o');
    foodBucket = new objPosArrayList();
/*
    food1.setObjPos(-10,-10,'o');
    food2.setObjPos(-20,-20,'o');
    food3.setObjPos(-25,-25,'o');
    food4.setObjPos(-30,-30,'o');
    special.setObjPos(-25,-25,'$');

    foodBucket->insertTail(food1);
    foodBucket->insertTail(food2);
    foodBucket->insertTail(food3);
    foodBucket->insertTail(food4);
    foodBucket->insertTail(special);*/
}

Food::~Food()
{
    delete foodBucket; 
}
Food::Food(const Food &f){

   


}
Food& Food::operator=(const Food &f){
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
    int x_bitvector[boardWidth + 1] = {0};
    int y_bitvector[boardHeight + 1] = {0};
    int x_positions[5] = {0}; //for storing random x positions 
    int y_positions[5] = {0}; // for storing random y positions

    int counter = 0; 
/*
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
*/

   

    while(counter<5){
        flag = 0;
        xFood = rand() % boardWidth + 1;
        yFood = rand() % boardHeight + 1;

        for(int i = 0; i < blockOff->getSize(); i++) { 
            objPos currentBlock = blockOff->getElement(i);
            if(xFood == currentBlock.pos->x && yFood == currentBlock.pos->y) { 
                flag = 1; //equal to snake position
                break;
            }
        }

        if(flag==0 && x_bitvector[xFood]== 0 && y_bitvector[yFood]==0){
            x_bitvector[xFood] = 1;
            y_bitvector[yFood] = 1;

            x_positions[counter] = xFood;
            y_positions[counter] = yFood;
            counter++;
        }
    }

    
    //foodPos.setObjPos(xFood, yFood,'o');
    food1.setObjPos(x_positions[0],y_positions[0],'o');
    food2.setObjPos(x_positions[1],y_positions[1],'o');
    food3.setObjPos(x_positions[2],y_positions[2],'o');
    food4.setObjPos(x_positions[3],y_positions[3],'o');
    special.setObjPos(x_positions[4],y_positions[4],'$');

    foodBucket->insertTail(food1);
    foodBucket->insertTail(food2);
    foodBucket->insertTail(food3);
    foodBucket->insertTail(food4);
    foodBucket->insertTail(special);

    x_positions[5] = {0}; //for storing random x positions 
    y_positions[5] = {0};

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


objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}   