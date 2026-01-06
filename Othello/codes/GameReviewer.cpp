#include "GameReviewer.h"
#include "Database/GameLogManager.h"
#include "Structures/Move.h"
#include "Structures/Board.h"
#include "conio.h"
#include <iostream>
#include <windows.h>

void executeGameReviewer(Board board)
{
    board.CursorX = -1;
    board.CursorY = -1;

    int logsCount = countLogs();

    int logId = -1;

    while (true)
    {
        system("cls");

        std::cout << "Press any key for next move, ESC to exit...\n";

        
        if (logId == -1)
        {
            board.newGameSetup();
            board.prepareBoardForMove('W');
        }
        else
        {
            Move move = getLog(logId);
            board.putPiece(move.x, move.y, move.color);
            if (move.color == 'B')
            {
                board.prepareBoardForMove('W');
            }
            else 
            {
                board.prepareBoardForMove('B');
            }
        }

        board.display();

        int userInput = _getch();

        if(userInput == 27)
        {
            break;
        }
        else
        {
            if (logId == logsCount - 1)
            {
                break;
            }
            logId++;
        }
    }

    system("cls");
}