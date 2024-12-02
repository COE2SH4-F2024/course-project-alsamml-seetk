#include "Food.h"
#include <cstdlib>
#include <time.h>
#include "objPos.h"


Food::Food()
{
    foodBucket = new objPosArrayList(); //initializing food bucket list on heap 
}

Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(GameMechs* gameMechsPtr, objPosArrayList* blockOff)
{
    srand(time(NULL)); // seed random integer generation with the current time  

    //retrieving board dimensions from game mechs 
    int boardWidth = gameMechsPtr->getBoardSizeX() - 2; //  board width excludes the border 
    int boardHeight = gameMechsPtr->getBoardSizeY() - 2; // board height excludes the border 

    int xFood, yFood; // to store randomly generated x,y positions
    int flag = 0;
    int counter = 0; 

    //initializing bit vector arrays to 0 to generate non repeating food positions
    int x_bitvector[boardWidth + 1] = {0};
    int y_bitvector[boardHeight + 1] = {0};
    //initializing arrays for storing x and y positions 
    int x_positions[5] = {0}; 
    int y_positions[5] = {0}; 


    //generating 5 random food items 
    while(counter < 5){
        flag = 0; //reset flag to 0 for each iteration 
        xFood = rand() % boardWidth + 1; //x position generated between [1,18]
        yFood = rand() % boardHeight + 1; //y position generated between [1,8]

        //iterating through the snake length (blockOff)
        for(int i = 0; i < blockOff->getSize(); i++) { 
            objPos currentBlock = blockOff->getElement(i);
            if(xFood == currentBlock.pos->x && yFood == currentBlock.pos->y) { 
                flag = 1; //generated position is equal to snake position, must generate new position
                break;
            }
        }

        //if coordinate is unique:
        if(flag==0 && x_bitvector[xFood]== 0 && y_bitvector[yFood]==0){
            //setting to 1 to prevent reuse of coordinate 
            x_bitvector[xFood] = 1; 
            y_bitvector[yFood] = 1;

            //store into list for x,y positions 
            x_positions[counter] = xFood;
            y_positions[counter] = yFood;
            counter++; //move onto generating next new position
        }
    }

    // using x,y coordinates from random food position list to set the food object parameters 
    food1.setObjPos(x_positions[0],y_positions[0],'o');
    food2.setObjPos(x_positions[1],y_positions[1],'o');
    food3.setObjPos(x_positions[2],y_positions[2],'o');
    food4.setObjPos(x_positions[3],y_positions[3],'o');
    special.setObjPos(x_positions[4],y_positions[4],'$');

    // inserting food objects into the food bucket
    foodBucket->insertTail(food1);
    foodBucket->insertTail(food2);
    foodBucket->insertTail(food3);
    foodBucket->insertTail(food4);
    foodBucket->insertTail(special);
}

objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}   