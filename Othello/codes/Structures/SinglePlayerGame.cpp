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
{
    clearGameLog();
    (*GameBoard).prepareBoardForMove(CurrentTurnColor);

    this -> save();

    while (true)
    {
        if (CurrentTurnColor != Player1 -> color) // Bot turn
        {
            Move botMove = GameBot -> suggestMove( (*GameBoard), CurrentTurnColor);
            GameBoard -> putPiece(botMove.x, botMove.y, CurrentTurnColor);

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
                    return;
                }
            }
        }

        system("cls");

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


void SinglePlayerGame::end()
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
            std::cout << "You lost. The bot won.\n";
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