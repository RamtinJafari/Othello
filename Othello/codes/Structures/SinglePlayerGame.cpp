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


SinglePlayerGame::SinglePlayerGame(Board GameBoard, Player* Player1, Bot* GameBot, char CurrentTurnColor)
{
    int lastId = getLastGameId();

    this -> id = lastId;
    this -> GameBoard = GameBoard;
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
    system("cls");
    clearGameLog();
    GameBoard.prepareBoardForMove(CurrentTurnColor);
    this -> save();

    while (true)
    {
        if (CurrentTurnColor != Player1 -> color)
        {
            GameBot -> decide(GameBoard, CurrentTurnColor);

            changeTurn();
            GameBoard.prepareBoardForMove(CurrentTurnColor);
            this -> save();

            if (GameBoard.countValidMoves() == 0)
            {
                changeTurn();
                GameBoard.prepareBoardForMove(CurrentTurnColor);
                this -> save();

                if (GameBoard.countValidMoves() == 0)
                {
                    end();
                }
            }
        }

        system("cls");
        char charCursorReplaced = GameBoard.placeCursor(CursorX, CursorY);
        GameBoard.display();

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == 72)
        {
            if (CursorY - 1 >= 0)
            {
                GameBoard.displayGrid[CursorY][CursorX] = charCursorReplaced;
                CursorY--;
                continue;
            }
        }

        else if (userInput == static_cast<int>('s') || userInput == 80)
        {
            if (CursorY + 1 < GameBoard.BoardSize)
            {
                GameBoard.displayGrid[CursorY][CursorX] = charCursorReplaced;
                CursorY++;
                continue;
            }
        }

        else if (userInput == static_cast<int>('a') || userInput == 75)
        {
            if (CursorX - 1 >= 0)
            {
                GameBoard.displayGrid[CursorY][CursorX] = charCursorReplaced;
                CursorX--;
                continue;
            }
        }

        else if (userInput == static_cast<int>('d') || userInput == 77)
        {
            if (CursorX + 1 < GameBoard.BoardSize)
            {
                GameBoard.displayGrid[CursorY][CursorX] = charCursorReplaced;
                CursorX++;
                continue;
            }
        }

        else if (userInput == 13)
        {
            if (GameBoard.displayGrid[CursorY][CursorX] == 'O')
            {
                GameBoard.putPiece(CursorX, CursorY, CurrentTurnColor);
                changeTurn();
                GameBoard.prepareBoardForMove(CurrentTurnColor);
                this -> save();

                if (GameBoard.countValidMoves() == 0)
                {
                    changeTurn();
                    GameBoard.prepareBoardForMove(CurrentTurnColor);
                    this -> save();

                    if (GameBoard.countValidMoves() == 0)
                    {
                        end();
                    }
                }
            }
        }
    }
}


void SinglePlayerGame::end()
// called when there is no valid moves remaining, the game is over
// Game decides the winner, declares the winner and saves the game for the last time
{
    int blackCount = GameBoard.countBlack();
    int whiteCount = GameBoard.countWhite();

    if (blackCount > whiteCount) 
    {
        Winner = (Player1 -> color == 'W' ? 1:2);
    }
    else if (whiteCount > blackCount)
    {
        Winner = (Player1 -> color == 'B' ? 1:2);
    }
    else
    {
        Winner == 3; // draw
    }

    this -> save();

    system("cls");
    GameBoard.display();

    std::cout << std::endl
        << (Winner == 1 ? 
            "Congratulations " + Player1 -> name + "!" + "\nYou won!\n":
            "You lost, bot won\n"
        )
        << std::endl;
}


void SinglePlayerGame::save()
// saves the game inside GameHistory.txt
{
    std::string gameToSave = this -> retrieveGame();
    saveGame(gameToSave);
}


void SinglePlayerGame::loadGame(int gameId)
// recreates this Game instance according to a game inside GameHistory.txt which its id is given
// the string being processed is created by retrieveGame method
{
    std::string game = getGameById(gameId);

    id = getGameId(game);
    GameBoard.loadBoard(getGameBoard(game));
    mode = getMode(game);
    Player1 -> loadPlayer(getPlayer1(game));
    GameBot -> loadBot(getBot(game));
    CurrentTurnColor = getCurrentTurnColor(game);
    Winner = getWinner(game);
}


std::string SinglePlayerGame::retrieveGame()
// turns current Game instance into a string
// this string can be turned into a Game instance via loadGame method
{
    std::string idToSave = intToStr(id);
    std::string boardToSave = GameBoard.retrieveBoard();
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