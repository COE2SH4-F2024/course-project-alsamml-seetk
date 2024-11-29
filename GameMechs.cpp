#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    
    boardSizeX = 20; 
    boardSizeY = 10; 
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor? no
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    
void GameMechs::collectAsyncInput()
{ 
    if(MacUILib_hasChar()) { 
        input = MacUILib_getChar();
    }

    //exit on escape key press
    if(input == 27) exitFlag = true;

}

char GameMechs::getInput() const
{
    // //get exit flag status 
    // getExitFlagStatus();

    // //get input from MacUILib
    // if(MacUILib_hasChar()) { 
    //     input = MacUILib_getChar();
    // }

    // //exit on escape key press
    // if(input != '\0') { 
    //     switch(input) { 
    //         case 27: 
    //             setExitTrue();
    //             break;
    //         default: break;
    //     }
    // }
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++; 
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here