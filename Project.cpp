#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
char input;
Player* myPlayer; 

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;
    myPlayer = new Player(nullptr);
    input = 0;



}

void GetInput(void)
{
   if (MacUILib_hasChar()){
        input = MacUILib_getChar();
    }

}

void RunLogic(void)
{
    //myPlayer->mainGameMechsRef->setInput(input);
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
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
   
   MacUILib_printf("Player[x,y]= [%d,%d], %c", playerPos.pos->x, playerPos.pos->y, playerPos.symbol ); 



}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    
    MacUILib_clearScreen();    
 delete myPlayer;
    MacUILib_uninit();
}
