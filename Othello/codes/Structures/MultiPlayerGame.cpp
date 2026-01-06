#include "../Database/GameHistoryManager.h"
#include "../Database/GameLogManager.h"
#include "../Utilities/IntToStr.h"
#include "../Utilities/SymbolToStr.h"
#include "Board.h"
#include "Player.h"
#include "MultiPlayerGame.h"
#include <conio.h>
#include <iostream>
#include <windows.h>


MultiPlayerGame::MultiPlayerGame(Board* GameBoard, Player* Player1, Player* Player2, char CurrentTurnColor)
{
    int lastId = getLastGameId();

    this -> id = lastId + 1;
    this -> GameBoard = GameBoard;
    this -> mode = "2Player";
    this -> Player1 = Player1;
    this -> Player2 = Player2;
    this -> CurrentTurnColor = CurrentTurnColor;
    this -> Winner = 0;
}


void MultiPlayerGame::changeTurn()
{
    if (CurrentTurnColor == 'B')
    {
        CurrentTurnColor = 'W';
    }
    else
    {
        CurrentTurnColor = 'B';
    }
}


void MultiPlayerGame::start()
{
    clearGameLog();
    (*GameBoard).prepareBoardForMove(CurrentTurnColor);

    this -> save();

    while (true)
    {
        system("cls");
        std::cout << (CurrentTurnColor == Player1 -> color ? Player2 -> name + "it's your turn" : Player2 -> name + "it's your turn") << std::endl;

        (*GameBoard).display();

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == 72)
        {
            if (GameBoard -> CursorY != 0)
            {
                GameBoard -> CursorY--;
            }
        }

        else if (userInput == static_cast<int>('s') || userInput == 80)
        {
            if (GameBoard -> CursorY != GameBoard -> BoardSize - 1)
            {
                GameBoard -> CursorY++;
            }
        }

        else if (userInput == static_cast<int>('a') || userInput == 75)
        {
            if (GameBoard -> CursorX != 0)
            {
                GameBoard -> CursorX--;
            }
        }

        else if (userInput == static_cast<int>('d') || userInput == 77)
        {
            if (GameBoard -> CursorX != GameBoard -> BoardSize - 1)
            {
                GameBoard -> CursorX++;
            }
        }

        else if (userInput == 13)
        {
            if ( (*GameBoard).validMovesGrid[GameBoard -> CursorY][GameBoard -> CursorX] == 'O')
            {
                (*GameBoard).putPiece(GameBoard -> CursorX, GameBoard -> CursorY, CurrentTurnColor);
                changeTurn();
                (*GameBoard).prepareBoardForMove(CurrentTurnColor);
                this -> save();

                if ((*GameBoard).countValidMoves() == 0)
                {
                    changeTurn();
                    (*GameBoard).prepareBoardForMove(CurrentTurnColor);
                    this -> save();

                    if ( (*GameBoard).countValidMoves() == 0)
                    {
                        end();
                        return;
                    }
                }
            }
        }
    }
}


void MultiPlayerGame::end()
{
    int blackCount =  (*GameBoard).countBlack();
    int whiteCount =  (*GameBoard).countWhite();

    system("cls");
    (*GameBoard).display();

    std::cout << "\nFinal Score: Black: " << blackCount 
        << " | White: " << whiteCount << "\n\n";

    if (blackCount > whiteCount) 
    {

        if (Player1->color == 'B') 
        {
            Winner = 1;  
            std::cout << "Congratulations " << Player1->name << "! You won!\n";
        } 
        else 
        {
            Winner = 2;
            std::cout << "Congratulations " << Player2->name << "! You won!\n";
        }
    }

    else if (whiteCount > blackCount) 
    {
        if (Player1->color == 'W') 
        {
            Winner = 1;
            std::cout << "Congratulations " << Player1->name << "! You won!\n";
        } 
        else 
        {
            Winner = 2;
            std::cout << "You lost. The bot won.\n";
        }
    }

    else 
    {
        Winner = 3;  // Draw
        std::cout << "It's a draw!\n";
    }

    this->save();
}


void MultiPlayerGame::save()
// saves the game inside GameHistory.txt
{
    saveGame(this);
}


std::string MultiPlayerGame::retrieveGame()
// turns current Game instance into a string
// this string can be turned into a Game instance via loadGame method
{
    std::string idToSave = intToStr(id);
    std::string boardToSave = (*GameBoard).retrieveBoard();
    std::string player1ToSave = Player1 -> retrievePlayer();
    std::string player2ToSave = Player2 -> retrievePlayer();
    std::string currentTurnToSave = symbolToStr(CurrentTurnColor);
    std::string winnerToSave = intToStr(Winner);

    return "[" + idToSave + "]["
        + boardToSave + "]["
        + mode + "]["
        + player1ToSave + "]["
        + player2ToSave + "]["
        + currentTurnToSave + "]["
        + winnerToSave + "]";
}
