#include "Config.h"
#include "Board.h"
#include "../Utilities/Print.h"
#include <iostream>
#include <string>

struct Board
{
    int BoardSize;
    char** grid;
    char** validMovesGrid;
    char** displayGrid;


//------------------------------- Constructor & deconstructor ----------------------------------------
    Board() 
    {
        BoardSize = Config::getInstance() -> BOARD_SIZE;

        grid = new char*[BoardSize];
        for (int i = 0; i < BoardSize; ++i) {
            grid[i] = new char[BoardSize];
        }

        validMovesGrid = new char*[BoardSize];
        for (int i = 0; i < BoardSize; ++i) {
            validMovesGrid[i] = new char[BoardSize];
        }

        displayGrid = new char*[BoardSize];
        for (int i = 0; i < BoardSize; ++i) {
            displayGrid[i] = new char[BoardSize];
        }

        resetValidMovesGrid();
    }


    void deleteBoardMemory()
    {
        for (int i = 0; i < BoardSize; ++i) 
        {
            delete[] grid[i];
        }
        delete[] grid;

        for (int i = 0; i < BoardSize; ++i) 
        {
            delete[] validMovesGrid[i];
        }
        delete[] validMovesGrid;

        for (int i = 0; i < BoardSize; ++i) 
        {
            delete[] displayGrid[i];
        }
        delete[] displayGrid;
    }


//-------------------------------- Database & pre-game operations ------------------------------------
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
        for (int y = 0; y < BoardSize; y++)
        {
            for (int x = 0; x < BoardSize; x++)
            {
                grid[y][x] = ' ';
            }
        }

        grid[BoardSize/2][BoardSize/2] = '○';
        grid[BoardSize/2 + 1][BoardSize/2 + 1] = '○';
        grid[BoardSize/2 + 1][BoardSize/2] = '⬤';
        grid[BoardSize/2][BoardSize/2 + 1] = '⬤';
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


// ------------------------------------- grid and game operations -----------------------------------------
    void prepareBoardForMove()
    {
        updateDisplayGrid();
        prepareValidMovesGrid();
        putValidMoves();
    } 


    void flip(int x, int y)
    {
        char piece = grid[y][x];

        if (piece == '⬤') grid[y][x] = '○';
        else if (piece == '○') grid[y][x] = '⬤';
    }


    void verticalflip(int x, int y, char color)
    {
        if (verticalNeighbour(x, y, color) == 0)
        {
            return;
        }

        // check up
        for (int i = y - 2; i > 0; i--)
        {
            if (grid[i][x] == color)
            {
                for (int a = y - 1; a > i; a--)
                {
                    flip(x, a);
                }
            }
        }

        // check down
        for (int i = y + 2; i < BoardSize; i++)
        {
            if (grid[i][x] == color)
            {
                for (int a = y + 1; a < i; a++)
                {
                    flip(x, a);
                }
            }
        }
    }


    void horazinalflip(int x, int y, char color)
    {
        if (horazinalNeighbour(x, y, color))
        {
            return;
        }

        // check left
        for (int i = x - 2; i > 0; i--)
        {
            if (grid[y][i] == color)
            {
                for (int a = x - 1; a > i; a--)
                {
                    flip(a, y);
                }
            }
        }

        // check right
        for (int i = x + 2; i < BoardSize; i++)
        {
            if (grid[y][i] == color)
            {
                for (int a = x + 1; a < i; a++)
                {
                    flip(a, y);
                }
            }
        }
    }


    void diagonalflip(int x, int y, char color)
    {
        // check right-up
        for (int i = x + 2, j = y - 2; i < BoardSize && j > 0; i++, j--)
        {
            if (grid[j][i] == color)
            {
                for(int a = x + 1, b = y - 1; a < i && b > j; a++, b--)
                {
                    flip(a, b);
                }
            }
        }

        // check right-down
        for (int i = x + 2, j = y + 2; i < BoardSize && j < BoardSize; i++, j++)
        {
            if (grid[j][i] == color)
            {
                for(int a = x + 1, b = y + 1; a < i && b < j; a++, b++)
                {
                    flip(a, b);
                }
            }
        }

        // check left-up
        for (int i = x - 2, j = y - 2; i > 0 && j > 0; i--, j--)
        {
            if (grid[j][i] == color)
            {
                for(int a = x - 1, b = y - 1; a > i && b > j; a--, b--)
                {
                    flip(a, b);
                }
            }
        }

        // check left-down
        for (int i = x - 2, j = y + 2; i > 0 && j < BoardSize; i--, j++)
        {
            if (grid[j][i] == color)
            {
                for(int a = x - 1, b = y + 1; a > i && b < j; a--, b++)
                {
                    flip(a, b);
                }
            }
        }
    }


    void putPiece(int x, int y, char color)
    {
        horazinalflip(x, y, color);
        verticalflip(x, y, color);
        diagonalflip(x, y, color);
    }


    int countBlack()
    {
        int count = 0;

        for (int y = 0; y < BoardSize; y++)
        {
            for (int x = 0; x < BoardSize; x++)
            {
                if (grid[y][x] == '⬤') count++;
            }
        }
    }


    int countWhite()
    {
        int count = 0;

        for (int y = 0; y < BoardSize; y++)
        {
            for (int x = 0; x < BoardSize; x++)
            {
                if (grid[y][x] == '○') count++;
            }
        }
    }


//------------------------------------------ validGrid operations --------------------------------------------
    bool isValid(int x, int y, char color)
    {
        if (grid[y][x] == '○' || grid[y][x] == '⬤')
            return false;

        return (diagonalNeighbour(x, y, color) != 0 || horazinalNeighbour(x, y, color) != 0 || verticalNeighbour(x, y, color) != 0);
    }


    int verticalNeighbour(int x, int y, char color)
    {
        int gain = 0;

        // check up
        for (int i = y - 2; i > 0; i--)
        {
            if (grid[i][x] == color)
            {
                gain += i - y - 1;
            }
        }

        // check down
        for (int i = y + 2; i < BoardSize; i++)
        {
            if (grid[i][x] == color)
            {
                gain += y - i - 1;
            }
        }

        return gain;
    }


    int horazinalNeighbour(int x, int y, char color)
    {
        int gain = 0;

        // check left
        for (int i = x - 2; i > 0; i--)
        {
            if (grid[y][i] == color)
            {
                gain += i - x - 1;
            }
        }

        // check right
        for (int i = x + 2; i < BoardSize; i++)
        {
            if (grid[y][i] == color)
            {
                gain += x - i - 1;
            }
        }

        return gain;
    }


    int diagonalNeighbour(int x, int y, char color)
    {
        int gain = 0;

        // check right-up
        for (int i = x + 2, j = y - 2; i < BoardSize && j > 0; i++, j--)
        {
            if (grid[j][i] == color)
            {
                gain += i - x - 1;
            }
        }

        // check right-down
        for (int i = x + 2, j = y + 2; i < BoardSize && j < BoardSize; i++, j++)
        {
            if (grid[j][i] == color)
            {
                gain += i - x - 1;
            }
        }

        // check left-up
        for (int i = x - 2, j = y - 2; i > 0 && j > 0; i--, j--)
        {
            if (grid[j][i] == color)
            {
                gain += x - i - 1;
            }
        }

        // check left-down
        for (int i = x - 2, j = y + 2; i > 0 && j < BoardSize; i--, j++)
        {
            if (grid[j][i] == color)
            {
                gain += x - i - 1;
            }
        }

        return gain;
    }


    void resetValidMovesGrid()
    {
        for (int y = 0; y < BoardSize; y++)
        {
            for (int x = 0; x < BoardSize; x++)
            {
                validMovesGrid[y][x] = ' ';
            }
        }
    }


    void prepareValidMovesGrid()
    {
        resetValidMovesGrid();

        for (int y = 0; y < BoardSize; y++)
        {
            for (int x = 0; x < BoardSize; x++)
            {
                if (isValid(x, y, grid[y][x]))
                    validMovesGrid[y][x] = '⦻';
            }
        }
    }


//----------------------------------- display and displayGrid operations -----------------------------------------
    void placeCursor(int x, int y)
    {
        displayGrid[y][x] = '⊙';
    }


    void updateDisplayGrid()
    {
        for (int y = 0; y < BoardSize; y++)
        {
            for (int x = 0; x < BoardSize; x++)
            {
                displayGrid[y][x] = grid[y][x];
            }
        }
    }


    void putValidMoves()
    {
        for (int y = 0; y < BoardSize; y++)
        {
            for (int x = 0; x < BoardSize; x++)
            {
                if (validMovesGrid[y][x] = '⦻')
                {
                    displayGrid[y][x] = '⦻';
                }
            }
        }
    }


    void display(int cursorX, int cursorY)
    {
        placeCursor(cursorX, cursorY);

        print("―", BoardSize * 2 + 2);
        std::cout << std::endl;

        for (int y = 0; y < BoardSize; y++)
        {
            std::cout << "|";
            for (int x = 0; x < BoardSize; x++)
            {
                std::cout << displayGrid[y][x] << "|";
            }
            std::cout << std::endl;
        }

        print("―", BoardSize * 2 + 2);
    }
};