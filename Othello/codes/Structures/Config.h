#pragma once

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
    Config();

public:
    static Config* getInstance();
    static void initialize();
    static void customizeBoardSize(int boardSize);
};