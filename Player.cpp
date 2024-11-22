#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = 10;
    playerPos.pos->y = 5;
    playerPos.symbol = '@'; //maybe change board size y and x later?
}


Player::~Player()
{
    // delete any heap members here
    //none
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic 
        
        // PPA3 input processing logic  
        if((mainGameMechsRef->getInput()) != 0)  // if not null character
    {
        switch(mainGameMechsRef->getInput())
        {                      
            case ' ':  // exit
                //exitFlag = true;
                break;

            // Add more key processing here
            // Add more key processing here
            // Add more key processing here
            case 'w':
                if (myDir == STOP || myDir == RIGHT || myDir ==LEFT){
                    myDir = UP;
                    
                }
                break;
            case 'a':
                if (myDir == STOP || myDir == UP || myDir ==DOWN){
                    myDir = LEFT;
                    
                }
                break;
            case 's':
                if (myDir == RIGHT || myDir == LEFT || myDir ==STOP){
                    myDir = DOWN;
                    
                }
                break;
            case 'd':
                if (myDir == STOP || myDir == DOWN || myDir ==UP){
                    myDir = RIGHT;
                    
                }
                break;
            default:
            //in initialize
                break;
        }
        
            
        
        
    }
    
         
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:
            playerPos.pos->y--; 
            if (playerPos.pos->y < 1){
                playerPos.pos->y = 8; // change to getter
            } 
            break;
        case RIGHT:
            playerPos.pos->x++;
            if (playerPos.pos->x > 18){
                playerPos.pos->x = 1;
            } 
            break;
        case DOWN:
            playerPos.pos->y++;
            if (playerPos.pos->y > 8){
                playerPos.pos->y = 1;
            } 
            break;
        case LEFT:
            playerPos.pos->x--;
            if (playerPos.pos->x < 1){
                playerPos.pos->x =18;
            } 
            break;
        case STOP: 
        //player positions in initalize
            break;
    }        
}

// More methods to be added