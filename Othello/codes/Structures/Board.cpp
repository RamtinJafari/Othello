#include "codes/Structures/Config.h"
#include "codes/Structures/Board.h"
#include "codes/Structures/Move.h"
#include "codes/Database/GameLogManager.h"
#include "codes/Utilities/Print.h"
#include "codes/Utilities/SymbolToStr.h"
#include <iostream>
#include <string>


//------------------------------- Constructor & deconstructor ----------------------------------------

Board::Board() 
// gets BoardSize from Config and allocates memort for matrixes
// intializes ValidMoves only, since grid will be intializes by GameMaster
// using newGameSetup or loadBoard methods
// also displayGrid is updated with grid before being diplayed
{
    BoardSize = Config::getInstance() -> BOARD_SIZE;

    grid = new char32_t*[BoardSize];
    for (int i = 0; i < BoardSize; ++i) {
        grid[i] = new char32_t[BoardSize];
    }

    validMovesGrid = new char32_t*[BoardSize];
    for (int i = 0; i < BoardSize; ++i) {
        validMovesGrid[i] = new char32_t[BoardSize];
    }

    displayGrid = new char32_t*[BoardSize];
    for (int i = 0; i < BoardSize; ++i) {
        displayGrid[i] = new char32_t[BoardSize];
    }

    resetValidMovesGrid();
}


void Board::deleteBoardMemory()
// when the game is over, this method has to be called to free up memory
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

std::string Board::retrieveBoard()
// turns grid into string format to be saved inside database
// this string can be used to create a grid using loadBoard method
{
    int index = 0;
    int size = BoardSize * BoardSize + BoardSize; 
    std::string result = "";

    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            result += grid[y][x];
            index++;
            if (x < BoardSize - 1)
            {
                result += ' ';
                index++;
            }
        }
    }
    
    return result;
}


void Board::newGameSetup()
// sets all grid elements to white-space except the four in center
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


void Board::loadBoard(std::string Board)
// recreates grid based on a string inside database
// this string is created by retrieveBoard method
{
    int index = 0;

    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            grid[y][x] = static_cast<char32_t>(Board[index]);
            index += 2;
        }
    }
}


// ------------------------------------- grid and game operations -----------------------------------------

void Board::prepareBoardForMove(char32_t thisTurnColor)
// this method has to be called when a valid move is made
// updated displayGrid with the latest changes in grid
// validMovesGrid will find valid moves based on the new grid
// if user has chosen to see valid moves inside the board (SHOW_AVAILABLE_PLACES_FOR_PIECES is set to true)
// then they are putted inside the displayGrid
{
    updateDisplayGrid();
    prepareValidMovesGrid(thisTurnColor);
    if (Config::getInstance() -> SHOW_AVAILABLE_PLACES_FOR_PIECES)
        putValidMoves();
} 


void Board::flip(int x, int y)
// simply changes the color of the piece inside the given coordinates (flips it)
{
    char32_t piece = grid[y][x];

    if (piece == '⬤') grid[y][x] = '○';
    else if (piece == '○') grid[y][x] = '⬤';
}


void Board::verticalflip(int x, int y, char32_t color)
// flips the surrounded pieces in vertical directions (up and down)
{
    if (verticalNeighbour(x, y, color) == 0)
    {
        return;
    }

    // check up
    for (int i = y - 2; i > 0; i--)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

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
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[i][x] == color)
        {
            for (int a = y + 1; a < i; a++)
            {
                flip(x, a);
            }
        }
    }
}


void Board::horazinalflip(int x, int y, char32_t color)
// flips the surrounded pieces in horazinal directions (left and right)
{
    if (horazinalNeighbour(x, y, color))
    {
        return;
    }

    // check left
    for (int i = x - 2; i > 0; i--)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

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
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[y][i] == color)
        {
            for (int a = x + 1; a < i; a++)
            {
                flip(a, y);
            }
        }
    }
}


void Board::diagonalflip(int x, int y, char32_t color)
// flips the surrounded pieces in diagonal directions
{
    // check right-up
    for (int i = x + 2, j = y - 2; i < BoardSize && j > 0; i++, j--)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

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
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

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
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

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
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[j][i] == color)
        {
            for(int a = x - 1, b = y + 1; a > i && b < j; a--, b++)
            {
                flip(a, b);
            }
        }
    }
}


void Board::putPiece(int x, int y, char32_t color)
// puts the piece inside grid and flips the pieces that are surounded now
// afterwards, logs the move made inside GameLog.txt for game review
// caution - this function considers that putting a piece in that coordination is valid
// since validation should be done in GameMaster
{
    grid[y][x] == color;

    Move move(x, y, color);
    addLog(move);

    horazinalflip(x, y, color);
    verticalflip(x, y, color);
    diagonalflip(x, y, color);
}


int Board::countBlack()
// counts the number of black pieces inside the grid
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


int Board::countWhite()
// counts the number of white pieces inside the grid
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


//------------------------------------------ validGrid operations --------------------------------------------

int Board::countValidMoves()
// returns the number of valid moves that can be made for the current turn
// should be called when validMovesGrid is created for the round
// in a nutshell, after preparedBoardForMove method is called
// used to see if the player has a move to make
{
    int count = 0;

    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            if (validMovesGrid[y][x] == '⦻') count++;
        }
    }

    return count;
}



int Board::isValid(int x, int y, char32_t color)
// returns the number of gains if a piece with the given color inside the given coordinations is placed
// if the number returns is bigger than zero, then the move is valid (legal)
{
    if (grid[y][x] == '○' || grid[y][x] == '⬤')
        return 0;

    return diagonalNeighbour(x, y, color) + horazinalNeighbour(x, y, color) + verticalNeighbour(x, y, color);
}



int Board::verticalNeighbour(int x, int y, char32_t color)
// returns the number of pieces that will be surounded in vertical directions
// if a piece with the given color is put in the given coordination
{
    int gain = 0;

    // check up
    for (int i = y - 2; i > 0; i--)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[i][x] == color)
        {
            gain += i - y - 1;
        }
    }

    // check down
    for (int i = y + 2; i < BoardSize; i++)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[i][x] == color)
        {
            gain += y - i - 1;
        }
    }

    return gain;
}


int Board::horazinalNeighbour(int x, int y, char32_t color)
// returns the number of pieces that will be surounded in horazinal directions
// if a piece with the given color is put in the given coordination
{
    int gain = 0;

    // check left
    for (int i = x - 2; i > 0; i--)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[y][i] == color)
        {
            gain += i - x - 1;
        }
    }

    // check right
    for (int i = x + 2; i < BoardSize; i++)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[y][i] == color)
        {
            gain += x - i - 1;
        }
    }

    return gain;
}


int Board::diagonalNeighbour(int x, int y, char32_t color)
// returns the number of pieces that will be surounded in diagonal directions
// if a piece with the given color is put in the given coordination
{
    int gain = 0;

    // check right-up
    for (int i = x + 2, j = y - 2; i < BoardSize && j > 0; i++, j--)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[j][i] == color)
        {
            gain += i - x - 1;
        }
    }

    // check right-down
    for (int i = x + 2, j = y + 2; i < BoardSize && j < BoardSize; i++, j++)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[j][i] == color)
        {
            gain += i - x - 1;
        }
    }

    // check left-up
    for (int i = x - 2, j = y - 2; i > 0 && j > 0; i--, j--)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[j][i] == color)
        {
            gain += x - i - 1;
        }
    }

    // check left-down
    for (int i = x - 2, j = y + 2; i > 0 && j < BoardSize; i--, j++)
    {
        char32_t oppColor = (color == '⬤' ? '○':'⬤');

        if (grid[i][x] == oppColor || grid[i][x] == ' ')
        {
            break;
        }

        if (grid[j][i] == color)
        {
            gain += x - i - 1;
        }
    }

    return gain;
}


void Board::resetValidMovesGrid()
// clears validGrid elements to white-space
{
    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            validMovesGrid[y][x] = ' ';
        }
    }
}


void Board::prepareValidMovesGrid(char32_t color)
// first ValidMovesGrid resets itself so previous data won't interupt the process
// then check each place in grid, if it's valid, it'll put ⦻ inside the coresponding coordinations inside itself
{
    resetValidMovesGrid();

    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            if (isValid(x, y, color) != 0)
                validMovesGrid[y][x] = '⦻';
        }
    }
}


//----------------------------------- display and displayGrid operations -----------------------------------------

char32_t Board::placeCursor(int x, int y)
// puts ⊙ as the cursor regardless of the element inside displayGrid
// returns the element that was in the coordination, so when the cursor
// moves, the previous element can be recovered
{
    char32_t curElement = displayGrid[y][x];
    displayGrid[y][x] = '⊙';
    return curElement;
}


void Board::updateDisplayGrid()
// displayGrid be copied based on the elements (pieces) inside grid
// displayGrid will be a copy of grid, in a nutshell
{
    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            displayGrid[y][x] = grid[y][x];
        }
    }
}


void Board::putValidMoves()
// validMovesGrid has the valid moves coordinations inside itself
// by calling this method, displayGrid will mark valid moves which
// validMovesGrid marks
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


void Board::display()
// outputs displayGrid with viasual decorations
{
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
        print("―", BoardSize * 2 + 2);
        std::cout << std::endl;
    }

    print("―", BoardSize * 2 + 2);
}