#include "Config.h"
#include "Board.h"
#include "Move.h"
#include "../Database/GameLogManager.h"
#include "../Utilities/Print.h"
#include "../Utilities/SymbolToStr.h"
#include <iostream>
#include <string>
#include <windows.h>


//------------------------------- Constructor & deconstructor ----------------------------------------

Board::Board(int boardSize) 
// gets BoardSize from Config and allocates memort for matrixes
// intializes ValidMoves only, since grid will be intializes by GameMaster
// using newGameSetup or loadBoard methods
// also displayGrid is updated with grid before being diplayed
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
// sets all grid elements to white-space except the four in center
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
// then they are putted inside the displayGrid
{
    updateDisplayGrid();
    prepareValidMovesGrid(thisTurnColor);
    if (Config::getInstance() -> SHOW_AVAILABLE_PLACES_FOR_PIECES)
        putValidMoves();
} 


// Simple flip a single piece
void Board::flip(int x, int y)
{
    if (grid[y][x] == 'B')
        grid[y][x] = 'W';
    else if (grid[y][x] == 'W')
        grid[y][x] = 'B';
}

// Main function: place a piece and flip all surrounded opponent pieces
void Board::putPiece(int x, int y, char color)
{
    // Place the new piece
    grid[y][x] = color;

    // Log the move
    Move move(x, y, color);
    addLog(move);

    // Directions: left, up, right, down, and diagonals
    const int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    const int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    // For each of the 8 directions
    for (int d = 0; d < 8; ++d) {
        int flips = countFlipsInDirection(x, y, dx[d], dy[d], color);
        if (flips > 0) {
            // Flip all opponent pieces in this direction
            int nx = x + dx[d];
            int ny = y + dy[d];
            for (int step = 0; step < flips; ++step) {
                flip(nx, ny);
                nx += dx[d];
                ny += dy[d];
            }
        }
    }
}


int Board::countBlack() {
    int count = 0;
    for (int y = 0; y < BoardSize; y++)
        for (int x = 0; x < BoardSize; x++)
            if (grid[y][x] == 'B') count++;
    return count;
}

int Board::countWhite() {
    int count = 0;
    for (int y = 0; y < BoardSize; y++)
        for (int x = 0; x < BoardSize; x++)
            if (grid[y][x] == 'W') count++;
    return count;
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
            if (validMovesGrid[y][x] == 'O') count++;
        }
    }

    return count;
}



int Board::isValid(int x, int y, char color)
{
    // Must be empty
    if (grid[y][x] != '.')
        return 0;

    // Must flip at least one opponent piece in at least one direction
    int totalFlips = 0;

    // Check all 8 directions
    const int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    const int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for (int d = 0; d < 8; ++d) {
        totalFlips += countFlipsInDirection(x, y, dx[d], dy[d], color);
    }

    return totalFlips;  // > 0 means valid move, value is how many pieces flipped
}


int Board::countFlipsInDirection(int x, int y, int dx, int dy, char color)
{
    char opp = (color == 'B' ? 'W' : 'B');

    int flips = 0;
    int nx = x + dx;
    int ny = y + dy;

    // Walk in the direction, counting opponent pieces
    while (nx >= 0 && nx < BoardSize && ny >= 0 && ny < BoardSize && grid[ny][nx] == opp) {
        flips++;
        nx += dx;
        ny += dy;
    }

    // If we didn't reach our own color at the end, this direction gives no valid flips
    if (nx < 0 || nx >= BoardSize || ny < 0 || ny >= BoardSize || grid[ny][nx] != color) {
        return 0;
    }

    // Otherwise, all the opponent pieces we passed will be flipped
    return flips;
}


void Board::resetValidMovesGrid()
// clears validGrid elements to white-space
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
// then check each place in grid, if it's valid, it'll put O inside the coresponding coordinations inside itself
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

char Board::placeCursor(int x, int y)
// puts X as the cursor regardless of the element inside displayGrid
// returns the element that was in the coordination, so when the cursor
// moves, the previous element can be recovered
{
    char curElement = displayGrid[y][x];
    displayGrid[y][x] = 'X';
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
    for (int y = 0; y < BoardSize; y++)
    {
        std::cout << "|";
        for (int x = 0; x < BoardSize; x++)
        {
            std::cout << symbolToStr(displayGrid[y][x]) << "|";
        }

        std::cout << std::endl;
    }
}