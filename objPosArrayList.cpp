#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.
#include <iostream>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
}

objPosArrayList::~objPosArrayList()
{
   delete[] aList;
}
objPosArrayList::objPosArrayList(const objPosArrayList &l){
    arrayCapacity = l.arrayCapacity;
    listSize = l.listSize;
    aList = new objPos[arrayCapacity];
    for( int i = 0; i<listSize; i++){
        aList[i] = l.aList[i];
    }
}
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &l){
    if (this!= &l){

        arrayCapacity = l.arrayCapacity;
        listSize = l.listSize;
        for(int i = 0; i<listSize; i++ ){
            aList[i] = l.aList[i];
        }

    }
    return *this;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize >= ARRAY_MAX_CAP) return;
    for ( int i = listSize; i>0; i--){
        aList[i] = aList[i-1];
    }
    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize >= arrayCapacity){
        std::cout<< "Array List Full. No Insertion." << std::endl;
        return;
    }
    aList[listSize++] = thisPos;
}

void objPosArrayList::removeHead()
{
    if (listSize ==0) return;
    for(int i = 0; i < listSize -1; i++)
    aList[i] = aList[i+1];
    listSize--;
    
}

void objPosArrayList::removeTail()
{
    if(listSize > 0)
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    if(listSize == 0) throw std::out_of_range("empty list");
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if(listSize == 0) throw std::out_of_range("empty list");
    return aList[listSize -1];
}

objPos objPosArrayList::getElement(int index) const
{
   /*if(index<0||index>listSize+1){
        throw std::out_of_range("Index out of bounds");
    }
*/ 
    return aList[index];
}