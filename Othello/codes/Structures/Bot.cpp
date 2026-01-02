#include "Bot.h"
#include "Board.h"
#include "../Utilities/IntToStr.h"
#include "../Utilities/StrToInt.h"
#include <string>

struct Bot
{
    std::string name;
    int difficulty;

    public:
    void decide(Board board)
    // the fucntion called by GameMaster when it's bot's turn to move
    // this function should be called when prepareBoardForMove is called
    // so bot will work as expected
    {
        if (difficulty == 1) // easy
        {
            easyDecide(board);
        }
        else if (difficulty == 2) // medium
        {
            mediumDecide(board);
        }
        else if (difficulty == 3) // hard
        {
            hardDecide(board);
        }
    }

    private:
    void easyDecide(Board borad)
    // the decision a bot would make in easy mode
    // the act is based on a random choice
    {

    }

    private:
    void mediumDecide(Board board)
    // the decision a bot would make in medium mode
    // the act is based on how much gain each move will have
    {

    }

    private:
    void hardDecide(Board board)
    // the decision a bot would make in hard mode
    {

    }

    public:
    std::string retrieveBot()
    {
        return name + "\"" + intToStr(difficulty);
    } 

    public:
    void loadBot(std::string bot)
    {
        int seperatorIndex = bot.find("\"");
        name = bot.substr(0, seperatorIndex - 1);
        difficulty = strToInt(bot.substr(seperatorIndex + 1, bot.size()));
    }
};