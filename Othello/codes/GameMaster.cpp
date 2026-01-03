// Player name should not have a | or [ or ] character within

#include <windows.h>
#include <conio.h>
#include <iostream>
#include "GameMaster.h"

void executeGameMaster(bool loadGameMode)
{
    if (loadGameMode) handleLoadGame();
    else handleNewGame();
}



void handleLoadGame()
{
    system("clr");

    std::cout << "You've chosen to load a previous unfinished game\n"
        << "Previous unfunished games are: \n";


}



void handleNewGame()
{

}