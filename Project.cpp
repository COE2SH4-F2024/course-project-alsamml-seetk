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

    myGM = new GameMechs();
    myPlayer = new Player(myGM);
    myFood = new Food();

    objPosArrayList* playerPosition = myPlayer->getPlayerPos();
    myFood->generateFood(myGM, playerPosition);

    objPos headPos (10, 5, '*');
    playerPosition-> insertHead(headPos);
    

}

void GetInput(void)
{
    myGM->collectAsyncInput();
    
    //debug key
    if(myGM->getInput() == 'r') {
        objPosArrayList* playerPosition = myPlayer->getPlayerPos();
        myFood->generateFood(myGM, playerPosition);

    MacUILib_printf("Food regenerated at new position\n");

    myGM->clearInput();

   } 

}

void RunLogic(void)
{
    //myPlayer->mainGameMechsRef->setInput(input);
    myPlayer->movePlayer();
    /*
    if(myPlayer->checkSelfCollision()) { 
        myGameMechs->setLoseFlag();
        myGameMechs->setExitTrue();
        return;
    }*/
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    int playerSize = playerPos->getSize();
    objPos foodPos = myFood->getFoodPos(); 


    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();


    for (int i = 0; i < boardY; i++){
        for(int j = 0; j < boardX; j++){
            int flag = 0; 

            //now iterate through playerPos array list to print all segments out 
            for(int k = 0; k < playerSize; k++) { 
                objPos thisSeg = playerPos->getElement(k);

                //check if current segment x, y pos matches j, i coordinate 
                if( i == thisSeg.pos->y && j == thisSeg.pos->x){
                    //if yes, print symbol 
                    MacUILib_printf("%c",thisSeg.symbol);
                    flag = 1;
                } 
            }

            //WATCH OUT - skip if-else block below if we have printed something
            //at end of for loop do something to determine whether to continue if-else or move onto next iteration of i-j
            if(flag == 1) continue; 

            //draw border
            if (i == 0 || i == boardY - 1 || j == 0 || j == boardX -1){
                MacUILib_printf("#");
            }
            else if(j == foodPos.pos->x && i == foodPos.pos->y) { 
                MacUILib_printf("%c",foodPos.symbol);
            }
            else{
                MacUILib_printf(" ");
            }
            
        }
        MacUILib_printf("\n");
   }
   objPos headPos = playerPos->getHeadElement();
   MacUILib_printf("================DEBUGGING===============\n");
   //MacUILib_printf("Player[x,y]= [%d,%d], %c\n", newHeadPos.pos->x, playerPos.pos->y, playerPos.symbol ); 
   MacUILib_printf("current score: %d\n", myGM -> getScore());
   MacUILib_printf("lose flg: %d ", myGM -> getLoseFlagStatus());
   MacUILib_printf("player head position: (%d, %d)\n", headPos.pos->x, headPos.pos->y);
   //("Player Direction: %d\n", myPlayer->myDir());
   MacUILib_printf("Game Board Size: (%d, %d)\n", myGM->getBoardSizeX(), myGM->getBoardSizeY());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 
    MacUILib_uninit();

    //end game messages
    myGM->getLoseFlagStatus() ? (MacUILib_printf("You Lost. Final Score: %d\n", myGM->getScore())) : (MacUILib_printf("Game Exited\n"));
    
    //delete allocated heap memory
    delete myGM;
    delete myPlayer;
    delete myFood;
}
