#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule
objPos::~objPos()
{
delete Pos;
}
objPos::objPos(const objPos &p)
{
  /*
  rowsNum = m.rowsNum;
	colsNum = m.colsNum;
	matrixData = new int*[rowsNum];
	for(int i = 0; i<rowsNum;i++){
		matrixData[i] = new int[colsNum];
		for(int j = 0; j<colsNum;j++){
			matrixData[i][j] = m.matrixData[i][j];
		}
	}
  */
 pos->x = p.pos->x;
 pos->y = p.pos->y;
 symbol = p.symbol;
 pos = new *Pos;

}
objPos& objPos::operator=(const objPos &p)
{
this->pos->x = p.pos->x;
 this->pos->y = p.pos->y;
 this->symbol = p.symbol;
}


void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
