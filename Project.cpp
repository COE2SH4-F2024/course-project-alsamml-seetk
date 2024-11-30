#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player* myPlayer; 
GameMechs* myGM;
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



}

void GetInput(void)
{
   myGM->collectAsyncInput();

}

void RunLogic(void)
{
    //myPlayer->mainGameMechsRef->setInput(input);
    myPlayer->updatePlayerDir();
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

objPos playerPos = myPlayer->getPlayerPos();
objPos foodPos = myFood->getFoodPos(); //already defined in food class??

int x = 0, y = 0;
   for (y=0; y<=9;y++){
    for(x=0;x<=19;x++){
        if (y==0 || y==9|| x==0 || x==19){
            MacUILib_printf("#");
        }
        else if(x == playerPos.pos->x && y==playerPos.pos->y){
            MacUILib_printf("%c",playerPos.symbol);
        }
        else if(x == foodPos.pos->x && y == foodPos.pos->y) { 
            MacUILib_printf("%c",foodPos.symbol);
        }
        else{
            MacUILib_printf(" ");
        }
        
    }
    MacUILib_printf("\n");
   }
   
   MacUILib_printf("================DEBUGGING===============\n");
   MacUILib_printf("Player[x,y]= [%d,%d], %c\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol ); 
   MacUILib_printf("current score: %d\n", myGM -> getScore());
  MacUILib_printf("lose flg: %d ", myGM -> getLoseFlagStatus());

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
