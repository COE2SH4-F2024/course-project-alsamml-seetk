#include "Player.h"
#include "ObjPos.h"


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

    //get head element of the player list 
    objPos currentHeadPos = playerPosList->getHeadElement();

    //create temp objPos to calculate new head pos
    objPos newHeadPos; 

    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:
            newHeadPos.setObjPos(currentHeadPos.pos->x, currentHeadPos.pos->y-1, '*');
            if (newHeadPos.pos->y <= 0) {
                newHeadPos.pos->y = mainGameMechsRef->getBoardSizeY() -2; // change to getter
            } 
            break;
        case RIGHT:
            newHeadPos.setObjPos(currentHeadPos.pos->x + 1, currentHeadPos.pos->y, '*');
            if (newHeadPos.pos->x >= mainGameMechsRef->getBoardSizeX() -1){
                newHeadPos.pos->x = 1;
            } 
            break;
        case DOWN:
            newHeadPos.setObjPos(currentHeadPos.pos->x, currentHeadPos.pos->y + 1, '*');
            if (newHeadPos.pos->y >= mainGameMechsRef->getBoardSizeY() -1){
                newHeadPos.pos->y = 1;
            } 
            break;
        case LEFT:
            newHeadPos.setObjPos(currentHeadPos.pos->x -1, currentHeadPos.pos->y, '*');
            if (newHeadPos.pos->x <= 0){
                newHeadPos.pos->x = mainGameMechsRef->getBoardSizeX() -2;
            } 
            break;
        case STOP: 
        //player positions in initalize
            break;
        default:
            return;
    }       

    //insert temp objPos to the head of the list
    playerPosList->insertHead(newHeadPos);

    //check if new temp objPos overlaps the food pos (get it from food class)
    // use isposequal() mmethod from objPos class
    //overlapped, food consumed, NO NOT REMOVE SNAKE TAIL
    //take respective actions to increase the score


    // If no overlap, remove tail, complete movement
    playerPosList->removeTail();

}

// More methods to be added