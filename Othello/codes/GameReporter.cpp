#include <iostream>
#include <conio.h>
#include <windows.h>
#include "codes/GameReporter.h"
#include "codes/Structures/Config.h"
#include "codes/DataBase/GameHistoryManager.h"
#include "codes/Utilities/outputDecoratedSavedGame.h"


void executeGameReporter()
{
    system("clr");

    std::cout << "Here is the history of the last "
        << Config::getInstance() -> GAME_HISTORY_LIMIT
        << " Played Games" << std::endl
        << "If you wish to change the number of saved games inside the history, you can change this number inside settings section of the game";

    int firstId = getFirstGameId();
    int lastId = getLastGameId();

    if (firstId == -1)
    {
        std::cout << "\n There are no games inside game history\n Press any key to continue";
        getch();
    }

    for (int id = lastId; id >= firstId; id--)
    {
        outputDecoratedSavedGame(getGameById(id));
    }

    std::cout << "\nPress any key to continue";
    getch();
}