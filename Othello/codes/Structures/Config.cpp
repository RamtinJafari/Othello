#include "ConfigManager.h"
#include "Config.h"
#include <iostream>
#include <windows.h>

struct Config
{
    static Config* instance;

    int GAME_HISTORY_LIMIT;
    int BOARD_SIZE;
    std::string BOARD_COLOR;
    std::string BOARD_BORDER_COLOR;
    bool SOUND;
    bool SHOW_AVAILABLE_PLACES_FOR_PIECES;
    bool HINT;
    int HINT_LIMIT;

    private: 
    Config() 
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

    static Config* getInstance()
    {
        if (!instance)
            throw 3; // config not initialized
        return instance;
    }

    static void initialize()
    {
        if (!instance)
            instance = new Config();
    }

    static void customizeBoardSize(int boardSize)
    {
        instance -> BOARD_SIZE = boardSize;
    }
};

Config* Config::instance = nullptr;
