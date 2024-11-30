#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();
    myDir = STOP;

    objPos headPos(thisGMRef->getBoardSizeX() / 2, thisGMRef->getBoardSizeY() /2, '*');

    playerPosList->insertHead(headPos);

    // more actions to be included
    // playerPos.pos->x = thisGMRef->getBoardSizeX() / 2;
    // playerPos.pos->y = thisGMRef->getBoardSizeY() /2;
    // playerPos.symbol = '@'; //maybe change board size y and x later?
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic 
        
        // PPA3 input processing logic  
      
        char input = mainGameMechsRef ->getInput();
        switch(input)
        {                      
            case 27:  // exit
                mainGameMechsRef->setExitTrue();
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

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    updatePlayerDir();

    //create temp objPos to calculate new head pos
    //get head element of the player list 
    

    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:
            playerPos.pos->y--; 
            if (playerPos.pos->y <= 0){
                playerPos.pos->y = mainGameMechsRef->getBoardSizeY() -2; // change to getter
            } 
            break;
        case RIGHT:
            playerPos.pos->x++;
            if (playerPos.pos->x >= mainGameMechsRef->getBoardSizeX() -1){
                playerPos.pos->x = 1;
            } 
            break;
        case DOWN:
            playerPos.pos->y++;
            if (playerPos.pos->y >= mainGameMechsRef->getBoardSizeY() -1){
                playerPos.pos->y = 1;
            } 
            break;
        case LEFT:
            playerPos.pos->x--;
            if (playerPos.pos->x <= 0){
                playerPos.pos->x = mainGameMechsRef->getBoardSizeX() -2;
            } 
            break;
        case STOP: 
        //player positions in initalize
            break;
    }        
}

// More methods to be added