#include "Config.h"
#include "Board.h"
#include "../Utilities/Print.h"
#include <string>

struct Board
{
    int BoardSize;
    char** grid;
    char** validMovesGrid;
    char** displayGrid;


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


    void prepareBoardForMove()
    {
        updateDisplayGrid();
        prepareValidMovesGrid();
        putValidMoves();
    } 


    void display(int cursorX, int cursorY)
    {
        placeCursor(cursorX, cursorY);

        print("―", BoardSize * 2 + 2);
        cout << endl;

        for (int y = 0; y < BoardSize; y++)
        {
            cout << "|";
            for (int x = 0; x < BoardSize; x++)
            {
                cout << displayGrid[y][x] << "|";
            }
            cout << endl;
        }

        print("―", BoardSize * 2 + 2);
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


    void flip(int x, int y)
    {
        char piece = grid[y][x];

        if (piece == '⬤') grid[y][x] = '○';
        else if (piece == '○') grid[y][x] = '⬤';
    }


    void verticalflip(int x, int y, char color)
    {
        if (verticalNeighbour(int x, int y, char color) == 0)
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
        if (horazinalNeighbour(int x, int y, char color))
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
        for (int i = x + 2, int j = y - 2; i < BoardSize && j > 0; i++, j--)
        {
            if (grid[j][i] == color)
            {
                for(int a = x + 1, int b = y - 1; a < i && b > j; a++, b--)
                {
                    flip(a, b);
                }
            }
        }

        // check right-down
        for (int i = x + 2, int j = y + 2; i < BoardSize && j < BoardSize; i++, j++)
        {
            if (grid[j][i] == color)
            {
                for(int a = x + 1, int b = y + 1; a < i && b < j; a++, b++)
                {
                    flip(a, b);
                }
            }
        }

        // check left-up
        for (int i = x - 2, int j = y - 2; i > 0 && j > 0; i--, j--)
        {
            if (grid[j][i] == color)
            {
                for(int a = x - 1, int b = y - 1; a > i && b > j; a--, b--)
                {
                    flip(a, b);
                }
            }
        }

        // check left-down
        for (int i = x - 2, int j = y + 2; i > 0 && j < BoardSize; i--, j++)
        {
            if (grid[j][i] == color)
            {
                for(int a = x - 1, int b = y + 1; a > i && b < j; a--, b++)
                {
                    flip(a, b);
                }
            }
        }
    }


    void putPiece(int x, int y, char color)
    {
        horazinalflip(int x, int y, char color);
        verticalflip(int x, int y, char color);
        diagonalflip(int x, int y, char color);
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
        for (int i = x + 2, int j = y - 2; i < BoardSize && j > 0; i++, j--)
        {
            if (grid[j][i] == color)
            {
                gain += i - x - 1;
            }
        }

        // check right-down
        for (int i = x + 2, int j = y + 2; i < BoardSize && j < BoardSize; i++, j++)
        {
            if (grid[j][i] == color)
            {
                gain += i - x - 1;
            }
        }

        // check left-up
        for (int i = x - 2, int j = y - 2; i > 0 && j > 0; i--, j--)
        {
            if (grid[j][i] == color)
            {
                gain += x - i - 1;
            }
        }

        // check left-down
        for (int i = x - 2, int j = y + 2; i > 0 && j < BoardSize; i--, j++)
        {
            if (grid[j][i] == color)
            {
                gain += x - i - 1;
            }
        }

        return gain;
    }


    bool isValid(int x, int y, char color)
    {
        if (grid[y][x] == '○' || grid[y][x] == '⬤')
            return false;

        return (diagonalNeighbour(int x, int y, char color) != 0 || horazinalNeighbour(int x, int y, char color) != 0 || verticalNeighbour(int x, int y, char color) != 0);
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
};