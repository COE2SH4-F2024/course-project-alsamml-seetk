#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;



//define and implement player class at top of project.cpp: 
class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPos getPlayerPos() const; // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here

    private:
        objPos playerPos; // Upgrade this in iteration 3.       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    /*initialize player initial position  position and symbol the same way as PPA3.
    From PPA3:
    player.x = 10;
    player.y = 5;
    player.symbol = 64;
    direction = STOP;*/
    PlayerPos = objPos(10, 5,'*');


    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic  
        if((mainGameMechsRef->getInput()) != 0)  // if not null character
    {
        switch(mainGameMechsRef)
        {                      
            case ' ':  // exit
                exiting = 1;
                exitFlag = 1;
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
    switch(direction)
    {
        case UP:
            pos->y--; 
            if (pos->y < 1){
                pos->y = mainGameMechsRef->boardSizeY-2;
            } 
            break;
        case RIGHT:
            pos->x++;
            if (pos->x > mainGameMechsRef->boardSizeX-2){
                pos->x = 1;
            } 
            break;
        case DOWN:
            pos->y++;
            if (pos->y > mainGameMechsRef->boardSizeY-2){
                pos->y = 1;
            } 
            break;
        case LEFT:
            pos->x--;
            if (pos->x < 1){
                pos->x = mainGameMechsRef->boardSizeY-2;
            } 
            break;
        case STOP: 
        //player positions in initalize
            break;
    }        
}

// More methods to be added




bool exitFlag;

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
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
