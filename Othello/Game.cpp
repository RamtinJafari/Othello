#include <iostream>
#include "/codes/Structures/Config.h"
#include "/codes/ConfigModifier.h"
#include <conio.h>
#include <windows.h>

int main()
{
    system("cls");
    
    Config::initialize();

    int chosenOption = 0;

    while (true)
    {
        system("cls");

        cout << "Welcome to Othello game!" << endl
            << (chosenOption == 0 ? "■":"□") << " new game" << endl
            << (chosenOption == 1 ? "■":"□") << " load game" << endl
            << (chosenOption == 2 ? "■":"□") << " help" << endl
            << (chosenOption == 3 ? "■":"□") << " games history" << endl
            << (chosenOption == 4 ? "■":"□") << " settings" << endl
            << (chosenOption == 5 ? "■":"□") << " exit" << endl;

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == 72)
        {
            if (chosenOption > 0)
            {
                chosenOption--;
                continue;
            }
        }

        if (userInput == static_cast<int>('s') || userInput == 80)
        {
            if (chosenOption < 5)
            {
                chosenOption++;
                continue;
            }
        }

         if (userInput == 13)
        {
            if (chosenOption == 0)
            {
                // new game
            }
            else if (chosenOption == 1)
            {
                // load game
            }
            else if (chosenOption == 2)
            {
                // help
            }
            else if (chosenOption == 3)
            {
                // games history
            }
            else if (chosenOption == 4)
            {
                ConfigModifier::execute();
            }
            else if (chosenOption == 5)
            {
                break;
            }
        }
    }

    return 0;
}