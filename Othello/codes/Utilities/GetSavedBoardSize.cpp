#include "codes/Database/GameHistoryManager.h"
#include "codes/Utilities/IntSqrt.h"
#include "codes/Utilities/GetSavedBoardSize.h"
#include <string>

int getSavedBoardSize(std::string board)
{
    int elementCount = getSavedBoardElementCount(board);
    return intSqrt(elementCount);
}