#include "../Database/GameHistoryManager.h"
#include "../Database/GameLogManager.h"
#include "../Utilities/IntToStr.h"
#include "../Utilities/SymbolToStr.h"
#include "Board.h"
#include "Bot.h"
#include "Player.h"
#include "SinglePlayerGame.h"
#include <conio.h>
#include <iostream>
#include <windows.h>


SinglePlayerGame::SinglePlayerGame(Board *GameBoard, Player* Player1, Bot* GameBot, char CurrentTurnColor)
{
    int lastId = getLastGameId();

    this -> id = lastId + 1;
    this ->  GameBoard =  GameBoard;
    this -> mode = "1Player";
    this -> Player1 = Player1;
    this -> GameBot = GameBot;
    this -> CurrentTurnColor = CurrentTurnColor;
    this -> Winner = 0;
}


void SinglePlayerGame::changeTurn()
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


void SinglePlayerGame::start()
// this method is called after:
//      player choosed to load a game and loadGame method was called
//      player choosed to create a new game, every object is created and prepared
{
    int CursorX = 0, CursorY = 0;

    clearGameLog();
     (*GameBoard).prepareBoardForMove(CurrentTurnColor);

    this -> save();

    while (true)
    {
        if (CurrentTurnColor != Player1 -> color)
        {
            GameBot -> decide( (*GameBoard), CurrentTurnColor);

            changeTurn();
             (*GameBoard).prepareBoardForMove(CurrentTurnColor);
            this -> save();

            if ( (*GameBoard).countValidMoves() == 0)
            {
                changeTurn();
                 (*GameBoard).prepareBoardForMove(CurrentTurnColor);
                this -> save();

                if ( (*GameBoard).countValidMoves() == 0)
                {
                    end();
                }
            }
        }

        system("cls");

        char charCursorReplaced =  (*GameBoard).placeCursor(CursorX, CursorY);

         (*GameBoard).display();

        int userInput = getch();

        if (userInput == static_cast<int>('w'))
        {
            if (CursorY - 1 >= 0)
            {
                 (*GameBoard).displayGrid[CursorY][CursorX] = charCursorReplaced;
                CursorY--;
                continue;
            }
        }

        else if (userInput == static_cast<int>('s'))
        {
            if (CursorY + 1 <  (*GameBoard).BoardSize)
            {
                 (*GameBoard).displayGrid[CursorY][CursorX] = charCursorReplaced;
                CursorY++;
                continue;
            }
        }

        else if (userInput == static_cast<int>('a'))
        {
            if (CursorX - 1 >= 0)
            {
                 (*GameBoard).displayGrid[CursorY][CursorX] = charCursorReplaced;
                CursorX--;
                continue;
            }
        }

        else if (userInput == static_cast<int>('d'))
        {
            if (CursorX + 1 <  (*GameBoard).BoardSize)
            {
                 (*GameBoard).displayGrid[CursorY][CursorX] = charCursorReplaced;
                CursorX++;
                continue;
            }
        }

        else if (userInput == 13)
        {
            if ( (*GameBoard).displayGrid[CursorY][CursorX] == 'O')
            {
                 (*GameBoard).putPiece(CursorX, CursorY, CurrentTurnColor);
                changeTurn();
                 (*GameBoard).prepareBoardForMove(CurrentTurnColor);
                this -> save();

                if ( (*GameBoard).countValidMoves() == 0)
                {
                    changeTurn();
                     (*GameBoard).prepareBoardForMove(CurrentTurnColor);
                    this -> save();

                    if ( (*GameBoard).countValidMoves() == 0)
                    {
                        end();
                    }
                }
            }
        }
    }
}


void SinglePlayerGame::end()
{
    int blackCount =  (*GameBoard).countBlack();   // Fixed in Board.cpp
    int whiteCount =  (*GameBoard).countWhite();

    system("cls");
     (*GameBoard).display();

    std::cout << "\nFinal Score: Black: " << blackCount 
              << " | White: " << whiteCount << "\n\n";

    if (blackCount > whiteCount) {
        if (Player1->color == 'B') {
            Winner = 1;  // Player wins
            std::cout << "Congratulations " << Player1->name << "! You won!\n";
        } else {
            Winner = 2;  // Bot wins
            std::cout << "You lost. The bot won.\n";
        }
    }
    else if (whiteCount > blackCount) {
        if (Player1->color == 'W') {
            Winner = 1;
            std::cout << "Congratulations " << Player1->name << "! You won!\n";
        } else {
            Winner = 2;
            std::cout << "You lost. The bot won.\n";
        }
    }
    else {
        Winner = 3;  // Draw
        std::cout << "It's a draw!\n";
    }

    this->save();
}


void SinglePlayerGame::save()
// saves the game inside GameHistory.txt
{
    saveGame(this);
}


std::string SinglePlayerGame::retrieveGame()
// turns current Game instance into a string
// this string can be turned into a Game instance via loadGame method
{
    std::string idToSave = intToStr(id);
    std::string boardToSave =  (*GameBoard).retrieveBoard();
    std::string playerToSave = Player1 -> retrievePlayer();
    std::string botToSave = GameBot -> retrieveBot();
    std::string currentTurnToSave = symbolToStr(CurrentTurnColor);
    std::string winnerToSave = intToStr(Winner);

    return "[" + idToSave + "]["
        + boardToSave + "]["
        + mode + "]["
        + playerToSave + "]["
        + botToSave + "]["
        + currentTurnToSave + "]["
        + winnerToSave + "]";
}