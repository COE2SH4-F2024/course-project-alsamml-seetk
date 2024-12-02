#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // direction state

        Player(GameMechs* thisGMRef, Food* thisfoodRef);
        ~Player();

        objPosArrayList* getPlayerPos() const;      
        void updatePlayerDir();
        void movePlayer();
        bool checkSelfCollision();
        int checkFoodConsumption(objPos newHeadPos);
        void increasePlayerLength(objPos newHeadPos);

    private: 
        objPosArrayList* playerPosList;     
        enum Dir myDir;

        GameMechs* mainGameMechsRef; // reference to main game mechanics 
        Food* foodRef; // reference to food class 
};

#endif