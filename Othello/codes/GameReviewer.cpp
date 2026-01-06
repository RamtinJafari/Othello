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
        system("cls");

        std::cout << "Press escape key to exit review mode \nPress any other key to see the next move \n\n";

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

        int userInput = getch();

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