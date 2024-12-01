#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "MacUILib.h"

using namespace std;

class Food 
{ 
    private: 
        objPos foodPos;

    public: 
        Food();
        ~Food();
        Food(const Food &f);
        Food& operator=(const Food &f);

        void generateFood(GameMechs* gameMechsPtr, objPosArrayList* blockOff);
        objPos getFoodPos() const;
};

#endif