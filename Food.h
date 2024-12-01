#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;

class Food 
{ 
    private: 
        //objPos foodPos;
        objPos food1;
        objPos food2;
        objPos food3;
        objPos food4;
        objPos special;
        objPosArrayList* foodBucket;

    public: 
        Food();
        ~Food();
        Food(const Food &f);
        Food& operator=(const Food &f);

        void generateFood(GameMechs* gameMechsPtr, objPosArrayList* blockOff, objPosArrayList* foodBucket);
        objPos getFoodPos() const;
};

#endif