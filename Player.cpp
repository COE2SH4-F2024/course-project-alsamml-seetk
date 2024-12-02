#include "Player.h"
#include "ObjPos.h"
#include "MacUILib.h"
#include "Food.h"
#include "objPosArrayList.h"

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    //obtaining reference of game mechs and food classes
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;

    playerPosList = new objPosArrayList(); // allocating new player in heap memory
    myDir = STOP; // default game state (not moving)

    //setting player's initial position at the center of the game board 
    int initialX = mainGameMechsRef->getBoardSizeX() /2;
    int initialY = mainGameMechsRef->getBoardSizeY() /2;
    objPos headPos(initialX,initialY, '*');

    playerPosList->insertHead(headPos); //starts with player length of 1 
}

Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList; // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    //settig game state based on key press input 
    switch(input)
    {                      
        case 27:  // exit case 
            mainGameMechsRef->setExitTrue();
            break;

        case 'w':
            if (myDir == STOP || myDir == RIGHT || myDir == LEFT){
                myDir = UP;
            }
            break;
        case 'a':
            if (myDir == STOP || myDir == UP || myDir == DOWN){
                myDir = LEFT; 
            }
            break;
        case 's':
            if (myDir == RIGHT || myDir == LEFT || myDir == STOP){
                myDir = DOWN;
            }
            break;
        case 'd':
            if (myDir == STOP || myDir == DOWN || myDir == UP){
                myDir = RIGHT; 
            }
            break;
        default:
            break;
    }      
}

void Player::movePlayer()
{
    updatePlayerDir(); // to move in required direction 

    //get head element of the player list
    objPos currentHeadPos = playerPosList->getHeadElement(); //temporary objPos used to calculate new head pos
    objPos newHeadPos = currentHeadPos; //new head position starts off at the current head position before calculation
    
    // snake movement and wrapparound logic
    switch(myDir)
    {
        case UP:
            newHeadPos.pos->y = currentHeadPos.pos->y - 1;
            if (newHeadPos.pos->y <= 0) {
                newHeadPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2; 
            } 
            break;
        case RIGHT:
            newHeadPos.pos->x = currentHeadPos.pos->x + 1;
            if (newHeadPos.pos->x >= mainGameMechsRef->getBoardSizeX() - 1){
                newHeadPos.pos->x = 1;
            } 
            break;
        case DOWN:
            newHeadPos.pos->y = currentHeadPos.pos->y + 1;
            if (newHeadPos.pos->y >= mainGameMechsRef->getBoardSizeY() - 1){
                newHeadPos.pos->y = 1;
            } 
            break;
        case LEFT:
            newHeadPos.pos->x = currentHeadPos.pos->x - 1;
            if (newHeadPos.pos->x <= 0){
                newHeadPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
            } 
            break;
        case STOP: 
            break;
        default:
           break;
    }  
         
    
    //performing actions beased on snake self collision 
    if(checkSelfCollision()){
        //if collision is detected, lose and exit game 
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }


    //performing actions based on food consumption (code segment lines 122 - 150)

    objPosArrayList* playerPosition = getPlayerPos();
    int foodConsumptionResult = checkFoodConsumption(newHeadPos); 

    // if snake has consumed an 'o':
    if(foodConsumptionResult == 0){
        //increment score and increase snake length
        mainGameMechsRef->incrementScore();
        increasePlayerLength( newHeadPos);

        foodRef->generateFood(mainGameMechsRef, playerPosition); // generate new random set of food item positions after collision
    }

    // if snake has consumed a '$':
    else if(foodConsumptionResult == 1){
        //increase score by 10 points 
        for(int j = 0; j<10; j++){
             mainGameMechsRef->incrementScore();
         }

         foodRef->generateFood(mainGameMechsRef, playerPosition); // generate new random set of food item positions after collision
    }

    //no collision with food 
    else if(foodConsumptionResult == 2){
        //regular snake movement 
        playerPosList->removeTail();
        playerPosList->insertHead(newHeadPos);
    }
}

bool Player::checkSelfCollision(){ 
    objPosArrayList* playerPosition = getPlayerPos(); 
    int listSize = playerPosList->getSize(); 
    objPos currentHeadPos = playerPosList->getHeadElement(); 
    
    for( int i = 1; i< listSize; i++){
        objPos currentPlayer = playerPosition->getElement(i);
        if(currentHeadPos.pos->x == currentPlayer.pos->x && currentHeadPos.pos->y == currentPlayer.pos->y){
            return true; //collision detected 
        }
    } return false; // no collision detected 
}

int Player::checkFoodConsumption(objPos newHeadPos){
    objPosArrayList* foodBucket = foodRef->getFoodPos();

    // iterating through food bucket to get each food object for comparison 
    for(int i = 0; i< foodBucket->getSize();i++){
        objPos currentFood = foodBucket->getElement(i);
        char foodSymbol = currentFood.getSymbolIfPosEqual(&newHeadPos); // if food and head object are equal(collision), obtain symbol of current food for processing

        //symbol processing 
        if (foodSymbol == 'o'){
            while (foodBucket->getSize() > 0) foodBucket->removeTail(); // empty food bucket for new food generation 
            return 0;
        }
        else if(foodSymbol == '$'){
            while (foodBucket->getSize() > 0) foodBucket->removeTail(); // empty food bucket for new food generation 
            return 1;
        }
    } return 2; // no collision 
}

void Player::increasePlayerLength(objPos newHeadPos){
    playerPosList->insertHead(newHeadPos); 
} 
