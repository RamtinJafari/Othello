#include "GameReviewer.h"
#include "Database/GameLogManager.h"
#include "Structures/Move.h"
#include "Structures/Board.h"
#include "conio.h"
#include <iostream>
#include <windows.h>

void executeGameReviewer(Board board)
{
    int logsCount = countLogs();

    int logId = -1;

    while (true)
    {
        system("clr");

        std::cout << "Press escape key to exit review mode \n\n";

        if (logId == -1)
        {
            board.newGameSetup();
            board.prepareBoardForMove('○');
        }
        else
        {
            Move move = getLog(logId);
            board.putPiece(move.x, move.y, move.color);
            if (move.color == '⬤')
            {
                board.prepareBoardForMove('○');
            }
            else 
            {
                board.prepareBoardForMove('⬤');
            }
        }

        board.display();

        int userInput = getch();

        if (userInput == static_cast<int>('a') || userInput == 37)
        {
            if (logId > -1)
            {
                logId--;
            }
        }

        else if (userInput == static_cast<int>('d') || userInput == 39)
        {
            if (logId < logsCount - 1)
            {
                logId++;
            }
        }

        else if(userInput == 27)
        {
            break;
        }
    }

    system("clr");
}