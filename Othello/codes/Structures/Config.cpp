#include "ConfigManager.h"
#include "Config.h"
#include <string>

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
            GAME_HISTORY_LIMIT = ConfigManager::getGameHistoryLimit(); 
            BOARD_SIZE = ConfigManager::getBoardSize(); 
            BOARD_COLOR = ConfigManager::getBoardColor(); 
            BOARD_BORDER_COLOR = ConfigManager::getBoardBorderColor(); 
            SOUND = ConfigManager::getSound(); 
            SHOW_AVAILABLE_PLACES_FOR_PIECES = ConfigManager::getShowAvailablePlacesForPieces(); 
            HINT = ConfigManager::getHint(); 
            HINT_LIMIT = ConfigManager::getHintLimit(); 
        } 
        catch (int errorCode) 
        { 
            if (errorCode == 1) 
            { 
                clrscr(); 
                cout << "An error acoured while opening Config.txt \nPerhaps another program is using it\nPress any key to continue"; 
                getchar(); 
            } 
            else if (int errorCode == 2) 
            { 
                clrscr(); 
                cout << "the inputed index is out of the bond of Config, the last index is 7\nPress any key to continue"; 
                getChar(); 
            } 
            else 
            { 
                clrscr(); 
                cout << "Unexpected error acoured\nPress any key to continue"; 
                getChar(); 
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
