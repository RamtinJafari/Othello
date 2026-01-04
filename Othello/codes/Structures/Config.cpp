#include "codes/Database/ConfigManager.h"
#include "codes/Structures/Config.h"
#include <iostream>
#include <windows.h>


Config* Config::instance = nullptr;
 
Config::Config() 
{ 
    try 
    { 
        GAME_HISTORY_LIMIT = getGameHistoryLimit(); 
        BOARD_SIZE = getBoardSize(); 
        BOARD_COLOR = getBoardColor(); 
        BOARD_BORDER_COLOR = getBoardBorderColor(); 
        SOUND = getSound(); 
        SHOW_AVAILABLE_PLACES_FOR_PIECES = getShowAvailablePlacesForPieces(); 
        HINT = getHint(); 
        HINT_LIMIT = getHintLimit(); 
    } 
    catch (int errorCode) 
    { 
        if (errorCode == 1) 
        { 
            system("cls"); 
            std::cout << "An error acoured while opening Config.txt \nPerhaps another program is using it\nPress any key to continue"; 
            getchar(); 
        } 
        else if (errorCode == 2) 
        { 
            system("cls"); 
            std::cout << "the inputed index is out of the bond of Config, the last index is 7\nPress any key to continue"; 
            getchar(); 
        } 
        else 
        { 
            system("cls"); 
            std::cout << "Unexpected error acoured\nPress any key to continue"; 
            getchar(); 
        } 
    }
}


Config* Config::getInstance()
{
    if (!instance)
        throw 3; // config not initialized
    return instance;
}


void Config::initialize()
{
    if (!instance)
        instance = new Config();
}


void Config::customizeBoardSize(int boardSize)
{
    if (instance)  // safety check
        instance->BOARD_SIZE = boardSize;
}