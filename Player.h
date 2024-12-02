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

        //objPos getPlayerPos() const; // Upgrade this in iteration 3. 
        objPosArrayList* getPlayerPos() const;      
        void updatePlayerDir();
        void movePlayer();
        bool checkSelfCollision();
        int checkFoodConsumption(objPos newHeadPos);
        void increasePlayerLength(objPos newHeadPos);

    private:
        //objPos playerPos; // Upgrade this in iteration 3.  
        objPosArrayList* playerPosList;     
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* foodRef;
};


#endif