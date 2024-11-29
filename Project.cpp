#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

Player* myPlayer; 
GameMechs* myGameMechs;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGameMechs->getExitFlagStatus() == false)  
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

    myGameMechs = new GameMechs();
    myPlayer = new Player(myGameMechs);



}

void GetInput(void)
{
   myGameMechs->getInput();

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
    myGameMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

objPos playerPos = myPlayer->getPlayerPos();
int x = 0, y = 0;
   for (y=0; y<=9;y++){
    for(x=0;x<=19;x++){
        if (y==0 || y==9|| x==0 || x==19){
            MacUILib_printf("#");
        }
        else if(x == playerPos.pos->x && y==playerPos.pos->y){
            MacUILib_printf("%c",playerPos.symbol);
        }
        else if(y==4 && x ==3){
            MacUILib_printf("*");
        }
        else if( x == 9 && y==6){
            MacUILib_printf("!");
        }
        else{
            MacUILib_printf(" ");
        }
        
    }
    MacUILib_printf("\n");
   }
   
   MacUILib_printf("================DEBUGGING===============\n");
   MacUILib_printf("Player[x,y]= [%d,%d], %c\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol ); 
   MacUILib_printf("current score: %d\n", myGameMechs -> getScore());
  MacUILib_printf("lose flg: %d ", myGameMechs -> getLoseFlagStatus());

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
    myGameMechs->getLoseFlagStatus() ? (MacUILib_printf("You Lost. Final Score: %d\n", myGameMechs->getScore())) : (MacUILib_printf("Game Exited\n"));
    
    //delete allocated heap memory
    delete myGameMechs;
    delete myPlayer;
}
