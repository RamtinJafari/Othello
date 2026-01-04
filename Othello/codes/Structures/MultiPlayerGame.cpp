#include "../Database/GameHistoryManager.h"
#include "../Database/GameLogManager.h"
#include "../Utilities/IntToStr.h"
#include "../Utilities/SymbolToStr.h"
#include "Board.h"
#include "Player.h"
#include "MultiPlayerGame.h"
#include <conio.h>
#include <iostream>


MultiPlayerGame::MultiPlayerGame(Board GameBoard, Player* Player1, Player* Player2, char32_t CurrentTurnColor)
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
    if (CurrentTurnColor == '⬤')
    {
        CurrentTurnColor = '○';
    }
    else
    {
        CurrentTurnColor = '⬤';
    }
}


void MultiPlayerGame::start()
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
        system("cls");
        char32_t charCursorReplaced = GameBoard.placeCursor(CursorX, CursorY);
        GameBoard.display();

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == 72)
        {
            if (CursorY - 1 > 0)
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

        else if (userInput == static_cast<int>('a') || userInput == 37)
        {
            if (CursorX - 1 > 0)
            {
                GameBoard.displayGrid[CursorY][CursorX] = charCursorReplaced;
                CursorX--;
                continue;
            }
        }

        else if (userInput == static_cast<int>('d') || userInput == 39)
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
            if (GameBoard.displayGrid[CursorY][CursorX] == '⦻')
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


void MultiPlayerGame::end()
// called when there is no valid moves remaining, the game is over
// Game decides the winner, declares the winner and saves the game for the last time
{
    int blackCount = GameBoard.countBlack();
    int whiteCount = GameBoard.countWhite();

    if (blackCount > whiteCount) 
    {
        Winner = (Player1 -> color == '○' ? 1:2);
    }
    else if (whiteCount > blackCount)
    {
        Winner = (Player1 -> color == '⬤' ? 1:2);
    }
    else
    {
        Winner == 3; // draw
    }

    this -> save();

    system("clr");
    GameBoard.display();

    GameBoard.deleteBoardMemory();

    std::cout << std::endl
        << (Winner == 1 ? 
            "Congratulations " + Player1 -> name + "!" + "\nYou won!\n":
            "Congratulations " + Player2 -> name + "!" + "\nYou won!\n"
        )
        << std::endl;
}


void MultiPlayerGame::save()
// saves the game inside GameHistory.txt
{
    std::string gameToSave = this -> retrieveGame();
    saveGame(gameToSave);
}


void MultiPlayerGame::loadGame(int gameId)
// recreates this Game instance according to a game inside GameHistory.txt which its id is given
// the string being processed is created by retrieveGame method
{
    std::string game = getGameById(gameId);

    id = getGameId(game);
    GameBoard.loadBoard(getGameBoard(game));
    mode = getMode(game);
    Player1 -> loadPlayer(getPlayer1(game));
    Player2 -> loadPlayer(getPlayer2(game));
    CurrentTurnColor = getCurrentTurnColor(game);
    Winner = getWinner(game);
}


std::string MultiPlayerGame::retrieveGame()
// turns current Game instance into a string
// this string can be turned into a Game instance via loadGame method
{
    std::string idToSave = intToStr(id);
    std::string boardToSave = GameBoard.retrieveBoard();
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
