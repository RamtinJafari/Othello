#include "ConfigModifier.h"
#include "/Database/ConfigManager.h"
#include <conio.h>



bool madeChanges = false;



void handleGameHistoryLimit();
void handleBoardSize();



void execute()
{
    int chosenOption = 0;

    while (true)
    {
        clrscr();

        cout << "curent setting are:" << endl
        << "The number of games inside game history: " << ConfigManager::getGameHistoryLimit() << endl
        << "The size of the board: " << ConfigManager::getBoardSize() << endl << endl;

        cout << "Which of these properties do you wish to change?" << endl;

        cout << (chosenOption == 0 ? "■":"□") << "The number of games inside game history" << endl
            << (chosenOption == 1 ? "■":"□") << "□ The size of the board" << endl
            << (chosenOption == 2 ? "■":"□") << "□ apply the changes and exit" << endl;

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == static_cast<int>('↑'))
        {
            if (chosenOption > 0)
            {
                chosenOption--;
                continue;
            }
        }

        if (userInput == static_cast<int>('s') || userInput == static_cast<int>('↓'))
        {
            if (chosenOption < 2)
            {
                chosenOption++;
                continue;
            }
        }

        if (userInput == static_cast<int>('⏎'))
        {
            if (chosenOption == 0)
            {
                handleGameHistoryLimit();
            }
            else if (chosenOption == 1)
            {
                handleBoardSize();
            }
            else if (chosenOption == 2)
            {
                break;
            }
        }
    }

    if (madeChanges == false) cout << "No changes has been made\nPress any key to continue"
    else if (madeChanges == true) cout << "Please restart the game for changes to be applied to the game\nPress any key to continue"

    getch();
    clrscr();
    return 0;
}



void handleGameHistoryLimit()
{
    clrscr();

    cout << "the current value of the number of games inside game history is "
        << ConfigManager::getGameHistoryLimit() << eld
        << "Please set the new value: " << endl;

    try
    {
        int newValue;
        cin >> newValue;
    }
    catch
    {
        cout << "invalid number inputed, please set a number\nPress any key to continue";
        getch();
        return handleGameHistoryLimit();
    }

    if (ConfigManager::getGameHistoryLimit == newValue)
    {
        return handleGameHistoryLimit();
    }

    if (newValue > 100)
    {
        cout << "Inputed number is too big, you might face slow loading when recieving reports or loading games"
            << endl << "Do you procced? [Y/N]" << endl;

        char procceded;
        cin >> procceded;
        
        if (!(procceded == 'Y' || procceded == 'y'))
        {
            return handleGameHistoryLimit();
        }
    }

    ConfigManager::modifyGameHistoryLimit(newValue);
    cout << "Change has been made\nPress any key to continue";
    getch();

    return 0;
}



void handleBoardSize()
{
    clrscr();

    cout << "the current value of the size of the board is "
        << ConfigManager::getBoardSize() << eld
        << "Please set the new value: " << endl;

    try
    {
        int newValue;
        cin >> newValue;
    }
    catch
    {
        cout << "invalid number inputed, please set a number\nPress any key to continue";
        getch();
        return handleBoardSize();
    }

    if (ConfigManager::getBoardSize() == newValue)
    {
        return handleBoardSize();
    }

    if (newValue > 50)
    {
        cout << "Inputed number is too big, please set a number lower than or equal to 50\nPress any key to continue" << endl;

        getch();

        return handleBoardSize();
    }

    ConfigManager::modifyBoardSize(newValue);
    cout << "Change has been made\nPress any key to continue";
    getch();

    return 0;
}