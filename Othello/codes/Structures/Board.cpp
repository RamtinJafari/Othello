#include "Config.h"
#include "Board.h"
#include "Move.h"
#include "../Database/GameLogManager.h"
#include "../Utilities/SymbolToStr.h"
#include <iostream>


//------------------------------- Constructor & deconstructor ----------------------------------------

Board::Board(int boardSize)
// grid holds the matrix used for game logic
// validMovesGrid is only used to show valid moves
// display grid is used to potentially combine grid and validMovesGrid for displaying the board
{
    BoardSize = boardSize;

    grid = new char*[boardSize];
    for (int i = 0; i < boardSize; ++i) {
        grid[i] = new char[boardSize];
    }

    validMovesGrid = new char*[boardSize];
    for (int i = 0; i < boardSize; ++i) {
        validMovesGrid[i] = new char[boardSize];
    }

    displayGrid = new char*[boardSize];
    for (int i = 0; i < boardSize; ++i) {
        displayGrid[i] = new char[boardSize];
    }

    for (int y = 0; y < boardSize; y++)
    {
        for (int x = 0; x < boardSize; x++)
        {
            grid[y][x] = '.';
            validMovesGrid[y][x] = '.';
            displayGrid[y][x] = '.';
        }
    }
}


void Board::deleteBoardMemory()
// when the game is over and maybe GameReviewer was executed
// this method has to be called to free up the allocated memory
// a destructor could do the job too
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
    int size = BoardSize * BoardSize + BoardSize; 
    std::string result = "";

    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            result += symbolToStr(grid[y][x]);

            if (!(y == BoardSize-1 && x == BoardSize-1))
            {
                result += "|";
            }
        }
    }
    
    return result;
}


void Board::newGameSetup()
// grid represents the starting state of the board when playing a new game
// called for board before passing its pointer for creating a SinglePlayerGame/MultiPlayerGame instance
{
    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            grid[y][x] = '.';
        }
    }

    grid[BoardSize/2 - 1][BoardSize/2 - 1] = 'W';
    grid[BoardSize/2][BoardSize/2] = 'W';
    grid[BoardSize/2][BoardSize/2 - 1] = 'B';
    grid[BoardSize/2 - 1][BoardSize/2] = 'B';

    updateDisplayGrid();
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
            grid[y][x] = static_cast<char>(Board[index]);
            index += 2;
        }
    }

    updateDisplayGrid();
}


// ------------------------------------- grid and game operations -----------------------------------------

void Board::prepareBoardForMove(char thisTurnColor)
// this method has to be called when a valid move is made
// updated displayGrid with the latest changes in grid
// validMovesGrid will find valid moves based on the new grid
// if user has chosen to see valid moves inside the board (SHOW_AVAILABLE_PLACES_FOR_PIECES is set to true)
// then they are putted inside the displayGrid (combining grid and validMovesGrid)
{
    updateDisplayGrid();
    prepareValidMovesGrid(thisTurnColor);
    if (Config::getInstance() -> SHOW_AVAILABLE_PLACES_FOR_PIECES)
        putValidMoves();
} 


void Board::flip(int x, int y)
// changes the color of the piece inside the given coordinates
{
    if (grid[y][x] == 'B')
        grid[y][x] = 'W';
    else if (grid[y][x] == 'W')
        grid[y][x] = 'B';
}


void Board::putPiece(int x, int y, char color)
{
    grid[y][x] = color;

    Move move(x, y, color);
    addLog(move);

    // each comnination of coresponding elements represent a diraction
    // left-up & left & left-down & up & down & right-uo & right & right-down
    const int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    const int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for (int d = 0; d < 8; ++d) 
    {
        int flips = countFlipsInDirection(x, y, dx[d], dy[d], color);

        if (flips > 0) 
        {
            int xc = x + dx[d];
            int yc = y + dy[d];

            for (int step = 0; step < flips; ++step) 
            {
                flip(xc, yc);
                xc += dx[d];
                yc += dy[d];
            }
        }
    }
}


int Board::countBlack() 
// counts the black pieces of the Board
{
    int count = 0;
    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            if (grid[y][x] == 'B') count++;
        }
    }

    return count;
}

int Board::countWhite() 
// counts the white pieces of the Board
{    
    int count = 0;
    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            if (grid[y][x] == 'W') count++;
        }
    }

    return count;
}


//------------------------------------------ validGrid operations --------------------------------------------

int Board::countValidMoves()
// returns the number of valid moves that can be made for the current turn
// should be called when validMovesGrid is created for the turn
// in a nutshell, after prepareBoardForMove method is called
// used to decide of a game has to end
{
    int count = 0;

    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            if (validMovesGrid[y][x] == 'O') count++;
        }
    }

    return count;
}



int Board::isValid(int x, int y, char color)
// returns the number of gains (opponent pieces fliped) if a piece with the given color is put in the given coords
// if it returns 0, then the move is inValid
// used as the primary parameter for the medium bot
{
    if (grid[y][x] != '.') return 0;

    int totalFlips = 0;

    // each comnination of coresponding elements represent a diraction
    // left-up & left & left-down & up & down & right-uo & right & right-down
    const int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    const int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for (int d = 0; d < 8; d++) 
    {
        totalFlips += countFlipsInDirection(x, y, dx[d], dy[d], color);
    }

    return totalFlips; 
}


int Board::countFlipsInDirection(int x, int y, int dx, int dy, char color)
// counts the number of flips happened by putting a piece with the given color inside the given coordinates
// dx and dy represent the direction and more specificly, the steps of x and y
{
    char oppColor = (color == 'B' ? 'W' : 'B');

    int flips = 0;
    int xc = x + dx;
    int yc = y + dy;

    
    while ((xc >= 0 && xc < BoardSize) && (yc >= 0 && yc < BoardSize) && grid[yc][xc] == oppColor) 
    {
        flips++;
        xc += dx;
        yc += dy;
    }

    // if loop doesn't meet a same colored piece, one of x coords or y coords will get out of bond
    // or the element loop breaked for is whether a '.' (empty place)
    if ((xc < 0 || xc == BoardSize) || (yc < 0 || yc == BoardSize) || grid[yc][xc] != color) 
    {
        return 0;
    }

    return flips;
}


void Board::resetValidMovesGrid()
// clears validGrid elements to empty places
{
    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            validMovesGrid[y][x] = '.';
        }
    }
}


void Board::prepareValidMovesGrid(char color)
// first ValidMovesGrid resets itself so previous data won't interupt the process
// then check each place in grid, if it's valid, it'll put O inside the coresponding coordinates inside itself
{
    resetValidMovesGrid();

    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            if (isValid(x, y, color) != 0)
                validMovesGrid[y][x] = 'O';
        }
    }
}


//----------------------------------- display and displayGrid operations -----------------------------------------
void Board::updateDisplayGrid()
// displayGrid be copied based on the elements (pieces) inside grid
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
// validMovesGrid has the valid moves coordinates inside itself
// by calling this method, displayGrid will mark valid moves which
// validMovesGrid marks
{
    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            if (validMovesGrid[y][x] == 'O')
            {
                displayGrid[y][x] = 'O';
            }
        }
    }
}


void Board::display()
// outputs displayGrid with viasual decorations
{
    std::cout << "    ";
    for (int i = 1; i <= BoardSize; i++)
    {
        std::cout << i << "  ";
    }
    std::cout << std::endl;

    std::cout << "  ";
    std::cout << (char)201;
    for (int i = 0; i < BoardSize; i++)
    {
        std::cout << (char)205 << (char)205 << (char)205;
    }
    std::cout << (char)187 << std::endl;

    for (int y = 0; y < BoardSize; y++)
    {
        std::cout << y + 1 << " " << (char)186;
        for (int x = 0; x < BoardSize; x++)
        {
            if (y == CursorY && x == CursorX) std::cout << "[";
            else std::cout << " ";

            char element = displayGrid[y][x];
            if (element == 'W') // white piece
            {
                std::cout << 'X';
            }
            else if (element == 'B') // black piece
            {
                std::cout << 'O';
            }
            else if (element == '.') // empty space
            {
                std::cout << ' ';
            }
            else if (element == 'O') // valid move
            {
                std::cout << (char)249; // ∙
            }

            if (y == CursorY && x == CursorX) std::cout << "]";
            else std::cout << " ";
        }
        std::cout << (char)186 << std::endl;
    }

    std::cout << "  ";
    std::cout << (char)200;
    for (int i = 0; i < BoardSize; i++)
    {
        std::cout << (char)205 << (char)205 << (char)205;
    }
    std::cout << (char)188 << std::endl;
}
// (char)186 = ║  (char)200 = ╚  (char)188 = ╝  (char)205 = ═  (char)206 = ╦  (char)202 = ╩  (char)187 =  ╗  (char)201 = ╔
// (char)79 = O
// (char)254 = ■