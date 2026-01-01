#include "Config.h"
#include "Board.h"
#include <string>

struct Board
{
    int BoardSize;
    char** grid;


    Board() 
    {
        BoardSize = Config::getInstance() -> BOARD_SIZE;

        grid = new char*[BoardSize];
        for (int i = 0; i < BoardSize; ++i) {
            grid[i] = new char[BoardSize];
        }
    }


    void display()
    {

    }


    void flip(int x, int y)
    {
        char piece = grid[y][x];

        if (piece == '■') grid[y][x] = '□';
        else if (piece == '□') grid[y][x] = '■';
    }


    void putPiece(int x, int y, char color)
    {

    }


    bool isValid(int x, int y, char color)
    {

    }


    int countBlack()
    {

    }


    int countWhite()
    {

    }


    std::string retrieveBoard()
    {
        int index = 0;
        int size = BoardSize * BoardSize + BoardSize; 
        char* savableBoard = new char[size];

        for (int y = 0; y < BoardSize; y++)
        {
            for (int x = 0; x < BoardSize; x++)
            {
                savableBoard[index] = grid[y][x];
                index++;
                if (x < BoardSize - 1)
                {
                    savableBoard[index] = ' ';
                    index++;
                }
            }
        }

        savableBoard[index] = '\0';

        std::string result(savableBoard);
        delete[] savableBoard;
        return result;
    }


    void newGameSetup()
    {

    }


    void loadBoard(std::string Board)
    {
        int index = 0;

        for (int y = 0; y < BoardSize; y++)
        {
            for (int x = 0; x < BoardSize; x++)
            {
                grid[y][x] = static_cast<char>(Board[index]);
                index += 2;
            }
        }
    }


    void deleteBoardMemory()
    {
        for (int i = 0; i < BoardSize; ++i) 
        {
            delete[] grid[i];
        }
        delete[] grid;
    }
};