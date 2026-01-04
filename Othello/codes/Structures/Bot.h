#pragma once

#include <string>
#include "codes/Structures/Board.h"

struct Bot
{
    std::string name;
    int difficulty;

    public:
    Bot(std::string name, int difficulty);
    void decide(Board board, char32_t color);
    std::string retrieveBot();
    void loadBot(std::string bot);

    private:
    void easyDecide(Board borad, char32_t color);
    void mediumDecide(Board board, char32_t color);
    void hardDecide(Board board, char32_t color);
};