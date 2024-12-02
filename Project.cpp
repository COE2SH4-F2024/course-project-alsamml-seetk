#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer; 
Food* myFood;



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //initializing objects on the heap 
    myGM = new GameMechs();
    myFood = new Food();
    myPlayer = new Player(myGM, myFood);

    objPosArrayList* playerPosition = myPlayer->getPlayerPos();
    objPosArrayList* foodBucket = myFood->getFoodPos();

    //initial generation of food on gameboard
    myFood->generateFood(myGM, playerPosition);
}

void GetInput(void)
{
    myGM->collectAsyncInput();
}

void RunLogic(void)
{
    myPlayer->movePlayer(); //contains logic related to player movement and collision 
    myGM->clearInput(); //clear input for next iteration 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  
   
    //obtaining variables for use in DrawScreen
    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    objPosArrayList* foodBucket = myFood->getFoodPos();
    int playerSize = playerPos->getSize();
    int foodBucketSize = foodBucket->getSize();

    //obtaining board dimensions from game mechs 
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    
    //iterating through board dimension
    for (int i = 0; i < boardY; i++){
        for(int j = 0; j < boardX; j++){
            int flag = 0; 

            //now iterate through playerPos array list to print all segments out 
            for(int k = 0; k < playerSize; k++) { 
                objPos thisSeg = playerPos->getElement(k);

                //check if current segment x,y position matches j,i coordinate 
                if( i == thisSeg.pos->y && j == thisSeg.pos->x){
                    MacUILib_printf("%c",thisSeg.symbol); //if yes, print symbol 
                    flag = 1;
                } 
            }
            
            if(flag == 1) continue; //skip if-else block below if we have printed the player 
           
           
            //printing the food object in foodbucket 
            for( int f = 0; f<foodBucketSize;f++ ){
                objPos thisFood = foodBucket->getElement(f);

                if ( i == thisFood.pos->y&& j == thisFood.pos->x){
                    MacUILib_printf("%c", thisFood.symbol);
                    flag = 1;
                }
            }
            if (flag ==1) continue; //skip if-else block below if we have printed the food 
            
            if (i == 0 || i == boardY - 1 || j == 0 || j == boardX -1){
                MacUILib_printf("#"); //draw border
            }
            else{
                MacUILib_printf(" "); //fill the rest of board with empty space
            }
            
        }
        MacUILib_printf("\n");
    }
    //printing game messages 
    MacUILib_printf("Current score: %d\n", myGM -> getScore());
    MacUILib_printf("Current Snake Length: %d\n", playerSize);
   
    MacUILib_printf("\n\nWelcome to the Snake Game! \n");
    MacUILib_printf("Consuming the 'o' increments your score by 1. Consuming the '$' increments your score by 10 without increasing snake length\n");
    MacUILib_printf("Press the esc button to exit the game\n");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //endgame messages
    myGM->getLoseFlagStatus() ? (MacUILib_printf("You Lost. Final Score: %d\n", myGM->getScore())) : (MacUILib_printf("Game Exited by Player\n"));
    
    MacUILib_uninit();

    //deallocate heap memory
    delete myGM;
    delete myPlayer;
    delete myFood;
}
