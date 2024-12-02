#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food 
{ 
    private: 
        //5 food objects within the food bucket list
        objPos food1;
        objPos food2;
        objPos food3;
        objPos food4;
        objPos special;

        objPosArrayList* foodBucket;

    public: 
        Food();
        ~Food();

        void generateFood(GameMechs* gameMechsPtr, objPosArrayList* blockOff);
        objPosArrayList* getFoodPos() const;
};

#endif