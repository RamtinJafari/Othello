#include "../Database/GameHistoryManager.h"
#include "IntSqrt.h"
#include <string>

int getSavedBoardSize(std::string board)
{
    int elementCount = getSavedBoardElementCount(board);
    return intSqrt(elementCount);
}