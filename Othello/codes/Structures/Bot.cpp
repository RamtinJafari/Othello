#include "Bot.h"
#include "Board.h"
#include "Move.h"
#include "../Utilities/IntToStr.h"
#include "../Utilities/StrToInt.h"
#include <string>
#include <random>
#include <climits>


    
Bot::Bot(std::string name, int difficulty)
{
    this -> name = name;
    this -> difficulty = difficulty;
}


Move Bot::suggestMove(Board& board, char color)
// the fucntion called by GameMaster when it's bot's turn to move
// this function should be called when prepareBoardForMove is called
// so bot will work as expected
{
    if (difficulty == 1) // easy
    {
        return suggestEasyMove(board, color);
    }
    else if (difficulty == 2) // medium
    {
        return suggestMediumMove(board, color);
    }
    else if (difficulty == 3) // hard
    {
        return suggestHardMove(board, color);
    }
    else
    {
        return suggestMediumMove(board, color); // fallback
    }
}



Move Bot::suggestEasyMove(Board& board, char color)
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
            if (board.validMovesGrid[y][x] == 'O')
            {
                if (moveNumber == randomNumber)
                {
                    Move move{x, y, color};
                    return move;
                }
                else
                {
                    moveNumber++;
                }
            }
        }
    }
}



Move Bot::suggestMediumMove(Board& board, char color)
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
            if (board.validMovesGrid[y][x] == 'O')
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

    Move move{moveX, moveY, color};
    return move;
}



Move Bot::suggestHardMove(Board& board, char color)
// the decision a bot would make in hard mode
{
    char oppColor = (color == 'W' ? 'B':'W');
    int index = 0;
    int validMovesCount = board.countValidMoves();

    Move moves[validMovesCount];

    for (int y = 0; y < board.BoardSize; y++)
    {
        for (int x = 0; x < board.BoardSize; x++)
        {
            if (board.validMovesGrid[y][x] == 'O')
            {
                Move move {x, y, color};
                moves[index] = move;
                index++;
            }
        }
    }

    Move bestMove = moves[0];
    int bestScore = INT_MIN;
    for (int i = 0; i < validMovesCount; i++)
    {
        Move move = moves[i];

        Board dummyBoard {board.BoardSize};

        deepCopy(board, dummyBoard);

        dummyBoard.putPiece(move.x, move.y, move.color);
        dummyBoard.prepareBoardForMove(oppColor);

        int score = minimax(oppColor, dummyBoard, false, color); // start minimizing since its user's turn

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
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
    name = bot.substr(0, seperatorIndex);
    difficulty = strToInt(bot.substr(seperatorIndex + 1, bot.size()));
}


//----------------------------------------- minimax algorithm ----------------------------------------------------
int ratePlacement(int x, int y, int boardSize)
// Board is passed by refrence for time optimization
// if we put a piece with these information, what score would the piece get
// for the coordinates itselves
{
    // corners
    if ((x == boardSize - 1 || x == 0) && (y == boardSize - 1 || y == 0)) 
        return 100;

    // leading to corner moves:
    else if (
        (x == boardSize - 2 && y == 1) ||
        (x == boardSize - 2 && y == boardSize - 2) ||
        (x == 1 && y == 1) ||
        (x == 1 && y == boardSize - 2)
    )
        return -50;
    else if (
        (x == boardSize - 2 && y == boardSize - 1) ||
        (x == boardSize - 2 && y == 0) ||
        (x == 1 && y == 0) ||
        (x == 1 && y == boardSize - 1) ||
        (x == boardSize - 1 && y == 1) ||
        (x == boardSize - 1 && y == boardSize - 2) ||
        (x == 0 && y == 1) ||
        (x == 0 && y == boardSize - 2)
    )
        return -30;

    // edges (corners and corner neighbour already handled)
    else if (x == 0 || x == boardSize - 1 || y == 0 || y == boardSize - 1)
        return 3;

    // center
    else if (
        (x == boardSize/2 && y == boardSize/2) ||
        (x == boardSize/2 && y == boardSize/2 - 1) ||
        (x == boardSize/2 - 1 && y == boardSize/2) ||
        (x == boardSize/2 - 1 && y == boardSize/2 - 1)
    )
        return 3;

    // other places have no value on their own
    return 0;
}


int rateBoard(Board& board, char botColor)
{
    char oppColor = (botColor == 'W' ? 'B':'W');

    Board dummyBoard {board.BoardSize};
    deepCopy(board, dummyBoard);

    int botScore = 0, playerScore = 0;

    // possible moves rating
    dummyBoard.prepareBoardForMove(botColor);
    botScore += dummyBoard.countValidMoves();

    dummyBoard.prepareBoardForMove(oppColor);
    botScore -= dummyBoard.countValidMoves();

    // greedy strategy
    int blackCount = dummyBoard.countBlack();
    int whiteCount = dummyBoard.countWhite();

    if (botColor == 'B')
    {
        botScore += blackCount;
        botScore -= whiteCount;
    }
    else
    {
        botScore -= blackCount;
        botScore += whiteCount;
    }

    // placement score
    for (int y = 0; y < board.BoardSize; y++)
    {
        for (int x =0; x < board.BoardSize; x++)
        {
            char element = board.grid[y][x];

            if (element == 'W' || element == 'B')
            {
                int score = ratePlacement(x, y, board.BoardSize);

                if (element == botColor)
                {
                    botScore += score;
                }
                else
                {
                    botScore -= score;
                }
            }
        }
    }

    return botScore;
}


int minimax(char color, Board dummyBoard, bool isMaxAgent, char botColor, int depth = 0, int upFloor = INT_MIN, int downFloor = INT_MAX)
{
    int index = 0;
    int validMovesCount = dummyBoard.countValidMoves();

    if (depth == 2 || validMovesCount == 0)
    {
        return rateBoard(dummyBoard, botColor);
    }

    Move moves[validMovesCount];

    for (int y = 0; y < dummyBoard.BoardSize; y++)
    {
        for (int x = 0; x < dummyBoard.BoardSize; x++)
        {
            if (dummyBoard.validMovesGrid[y][x] == 'O')
            {
                Move move {x, y, color};
                moves[index] = move;
                index++;
            }
        }
    }

    if (isMaxAgent) // maximizing
    {
        int curMax = INT_MIN;

        // for each valid move in this turn
        for (int i = 0; i < validMovesCount; i++)
        {
            Move move = moves[i];
            
            Board newBoard{dummyBoard.BoardSize};

            deepCopy(dummyBoard, newBoard);
            newBoard.putPiece(move.x, move.y, move.color);
            newBoard.prepareBoardForMove(move.color == 'B' ? 'W':'B');

            int minAgentAnswer = minimax((move.color == 'B' ? 'W':'B'), newBoard, false, botColor, depth + 1, upFloor, downFloor);

            curMax = std::max(curMax, minAgentAnswer);
            upFloor = std::max(upFloor, curMax);  

            if (upFloor >= downFloor) break;
        }

        return curMax;
    }

    else // minimizing
    {
        int curMin = INT_MAX;

        // for each valid move in this turn
        for (int i = 0; i < validMovesCount; i++)
        {
            Move move = moves[i];

            Board newBoard{dummyBoard.BoardSize};

            deepCopy(dummyBoard, newBoard);
            newBoard.putPiece(move.x, move.y, move.color);
            newBoard.prepareBoardForMove(move.color == 'B' ? 'W':'B');

            int maxAgentAnswer = minimax((move.color == 'B' ? 'W':'B'), newBoard, true, botColor, depth + 1, upFloor, downFloor);

            curMin = std::min(curMin, maxAgentAnswer);
            downFloor = std::min(downFloor, curMin);

            if (upFloor >= downFloor) break;
        }

        return curMin;
    }
}


void deepCopy(Board& board, Board& newBoard)
{
    for (int y = 0; y < board.BoardSize; y++)
    {
        for (int x = 0; x < board.BoardSize; x++)
        {
            newBoard.grid[y][x] = board.grid[y][x];
        }
    }
}