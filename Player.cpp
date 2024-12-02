#include "Player.h"
#include "ObjPos.h"
#include "MacUILib.h"
#include "Food.h"
#include "objPosArrayList.h"

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;

    playerPosList = new objPosArrayList();
    myDir = STOP;
    int initialX = mainGameMechsRef->getBoardSizeX() /2;
    int initialY = mainGameMechsRef->getBoardSizeY() /2;
    objPos headPos(initialX,initialY, '*');


    playerPosList->insertHead(headPos);
   

    // more actions to be included
    
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
    objPos newHeadPos = currentHeadPos; 

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
           break;
       
    }  
         
    
    //check if new temp objPos overlaps the food pos (get it from food class)
    // use isposequal() mmethod from objPos class

    if(checkSelfCollision()){
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    
    }
    int foodConsumptionResult = checkFoodConsumption(newHeadPos);
    if(foodConsumptionResult ==0){
        mainGameMechsRef->incrementScore();
        //increasePlayerLength();
        increasePlayerLength( newHeadPos);

    }
    else if(foodConsumptionResult == 1){
        for(int j = 0; j<10; j++){
             mainGameMechsRef->incrementScore();

         }

    }
    else if(foodConsumptionResult==2){
       // increasePlayerLength();
        playerPosList->removeTail();
        playerPosList->insertHead(newHeadPos);
    }
    /*
        objPosArrayList* foodBucket = foodRef->getFoodPos();
        for(int i = 0; i< foodBucket->getSize();i++){
            objPos currentFood = foodBucket->getElement(i);
            if(newHeadPos.isPosEqual(&currentFood)){
                objPosArrayList* playerPosition = getPlayerPos();
                
                while (foodBucket->getSize() > 0){
                    foodBucket->removeTail();
                }
                foodRef->generateFood(mainGameMechsRef, playerPosition);
                if (currentFood.symbol == 'o'){
                    mainGameMechsRef->incrementScore();
                    playerPosList->insertHead(newHeadPos);
                }
                else if(currentFood.symbol == '$'){
                    for(int j = 0; j<10; j++){
                        mainGameMechsRef->incrementScore();

                    }
                }
                return;
                
            }
            
        
        }
        playerPosList->insertHead(newHeadPos);
                playerPosList->removeTail();

        
            //true
            //if statements for symbols 
            //do action
        objPosArrayList* foodBucket = foodRef->getFoodPos();
        for(int i = 0; i< foodBucket->getSize();i++){
            objPos currentFood = foodBucket->getElement(i);
            
            if(checkFoodConsumption()){

                objPosArrayList* playerPosition = getPlayerPos();
                while (foodBucket->getSize() > 0){
                    foodBucket->removeTail();
                }
                foodRef->generateFood(mainGameMechsRef, playerPosition);
    
                if (currentFood.symbol == 'o'){
                    mainGameMechsRef->incrementScore();
                    playerPosList->insertHead(newHeadPos);
                }
                else if(currentFood.symbol == '$'){
                    for(int j = 0; j<10; j++){
                        mainGameMechsRef->incrementScore();
                    }
                }
                return;
        }
        
                
                
        }
            //false
            playerPosList->insertHead(newHeadPos);
            playerPosList->removeTail();*/
        
        //objPos foodPos = foodRef->getFoodPos();
       /* if(newHeadPos.isPosEqual(&foodPos)) { 
            //overlapped, food consumed, NO NOT REMOVE SNAKE TAIL
            //take respective actions to increase the score
            objPosArrayList* playerPosition = getPlayerPos();
            foodRef->generateFood(mainGameMechsRef, playerPosition);
            mainGameMechsRef->incrementScore();
        }
        else { 
            // If no overlap, remove tail, complete movement
            playerPosList->removeTail();
        }
        //insert temp objPos to the head of the list in either case 
        //->insertHead(newHeadPos); */
    

}
/*for(int i = 0; i < blockOff->getSize(); i++) { 
            objPos currentBlock = blockOff->getElement(i);
            if(xFood == currentBlock.pos->x && yFood == currentBlock.pos->y) { 
                flag = 1; //equal to snake position
                break;
            }*/

// More methods to be added
bool Player::checkSelfCollision(){ 
    objPosArrayList* playerPosition = getPlayerPos(); 
    int listSize = playerPosList->getSize(); 
    objPos currentHeadPos = playerPosList->getHeadElement(); 
    
    for( int i = 1; i< listSize; i++){
        objPos currentPlayer = playerPosition->getElement(i);
        if(currentHeadPos.pos->x == currentPlayer.pos->x && currentHeadPos.pos->y == currentPlayer.pos->y){
            
            return true;
        }
    } return false;
}

int Player::checkFoodConsumption(objPos newHeadPos){
    /*
    objPosArrayList* foodBucket = foodRef->getFoodPos();
        for(int i = 0; i< foodBucket->getSize();i++){
            objPos currentFood = foodBucket->getElement(i);
            if(newHeadPos.isPosEqual(&currentFood)){
                return true;
            }
            
}return false;*/
//objPos newHeadPos = playerPosList->getHeadElement();
objPosArrayList* foodBucket = foodRef->getFoodPos();
        for(int i = 0; i< foodBucket->getSize();i++){
            objPos currentFood = foodBucket->getElement(i);
            if(newHeadPos.isPosEqual(&currentFood)){
                objPosArrayList* playerPosition = getPlayerPos();
                
                while (foodBucket->getSize() > 0){
                    foodBucket->removeTail();
                }
                foodRef->generateFood(mainGameMechsRef, playerPosition);
                if (currentFood.symbol == 'o'){
                    return 0;
                }
                else if(currentFood.symbol == '$'){
                  return 1;
                }
                
                
            }
            
        
        }return 2;

       
}

void Player::increasePlayerLength(objPos newHeadPos){
    playerPosList->insertHead(newHeadPos);
    
} 
