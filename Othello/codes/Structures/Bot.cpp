#include "Bot.h"
#include "Board.h"
#include "../Utilities/IntToStr.h"
#include "../Utilities/StrToInt.h"
#include <string>
#include <random>


    
Bot::Bot(std::string name, int difficulty)
{
    this -> name = name;
    this -> difficulty = difficulty;
}


void Bot::decide(Board board, char32_t color)
// the fucntion called by GameMaster when it's bot's turn to move
// this function should be called when prepareBoardForMove is called
// so bot will work as expected
{
    if (difficulty == 1) // easy
    {
        easyDecide(board, color);
    }
    else if (difficulty == 2) // medium
    {
        mediumDecide(board, color);
    }
    else if (difficulty == 3) // hard
    {
        hardDecide(board, color);
    }
}



void Bot::easyDecide(Board board, char32_t color)
// the decision a bot would make in easy mode
// the act is based on a random choice
{
    int validMovesCount = board.countValidMoves();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, validMovesCount-1);        
    int randomNumber = distrib(gen);

    int moveNumber = 0;
    for (int y = 0; y < board.BoardSize; y++)
    {
        for (int x = 0; x < board.BoardSize; x++)
        {
            if (board.validMovesGrid[y][x] == '⦻')
            {
                if (moveNumber == randomNumber)
                {
                    board.putPiece(x, y, color);
                }
                else
                {
                    moveNumber++;
                }
            }
        }
    }
}



void Bot::mediumDecide(Board board, char32_t color)
// the decision a bot would make in medium mode
// the act is based on how much gain each move will have
// the move with the most gain is made
{
    int moveX, moveY;
    int maxGain = 0;

    for (int y = 0; y < board.BoardSize; y++)
    {
        for (int x = 0; x < board.BoardSize; x++)
        {
            if (board.validMovesGrid[y][x] == '⦻')
            {
                int gain = board.isValid(x, y, color);
                if (gain > maxGain)
                {
                    moveY = y;
                    moveX = x;
                    maxGain = gain;
                }
            }
        }
    }

    board.putPiece(moveX, moveY, color);
}



void Bot::hardDecide(Board board, char32_t color)
// the decision a bot would make in hard mode
{
    // do later
}



std::string Bot::retrieveBot()
// turns Bot structure into a string to be saved inside database
// this string will be loaded using loadBot method
{
    return name + "|" + intToStr(difficulty);
} 



void Bot::loadBot(std::string bot)
// fills Bot's properties according to the given string 
// this string is bot's informating saved inside database
// this string was made using retrieveBot method
{
    int seperatorIndex = bot.find("|");
    name = bot.substr(0, seperatorIndex - 1);
    difficulty = strToInt(bot.substr(seperatorIndex + 1, bot.size()));
}
