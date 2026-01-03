#pragma once

#include <string>

struct Bot
{
    std::string name;
    int difficulty;

    public:
    Bot(std::string name, int difficulty);
    void decide(Board board, char color);
    std::string retrieveBot();
    void loadBot(std::string bot);

    private:
    void easyDecide(Board borad, char color);
    void mediumDecide(Board board, char color);
    void hardDecide(Board board, char color);
};