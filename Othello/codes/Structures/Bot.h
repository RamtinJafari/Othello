#pragma once

#include <string>

struct Bot
{
    std::string name;
    int difficulty;

    public:
    void decide(Board board);
    std::string retrieveBot();
    void loadBot(std::string bot);

    private:
    void easyDecide(Board borad);
    void mediumDecide(Board board);
    void hardDecide(Board board);
};