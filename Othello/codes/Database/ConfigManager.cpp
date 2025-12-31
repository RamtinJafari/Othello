#include <iostream>
#include <fstream>
#include "../Utilities/StrToInt.h"

using namespace std;

int getGameHistoryLimit() 
{
    ifstream file ("Config.txt");

    if (file.is_open())
    {
        string line;
        getline(file, line);
        getline(file, line);

        int startingIndex = line.find("=") + 2;
        string GameHistoryLimit = line.substr(startingIndex, line.size());

        return StrToInt(GameHistoryLimit);

        file.close();
    }
    else 
    {
        clrscr();
        cout << "An error acoured while opening Config.txt \nPerhaps another program is using it\nPress any key to continue";
        getchar();
    }
}

int getBoardSize() 
{
    ifstream file ("Config.txt");

    if (file.is_open())
    {
        string line;
        getline(file, line);
        getline(file, line);

        int startingIndex = line.find("=") + 2;
        string GameHistoryLimit = line.substr(startingIndex, line.size());

        return StrToInt(GameHistoryLimit);

        file.close();
    }
    else 
    {
        clrscr();
        cout << "An error acoured while opening Config.txt \nPerhaps another program is using it\nPress any key to continue";
        getchar();
    }
}

int getGameHistoryLimit() 
{
    ifstream file ("Config.txt");

    if (file.is_open())
    {
        string line;
        getline(file, line);
        getline(file, line);

        int startingIndex = line.find("=") + 2;
        string GameHistoryLimit = line.substr(startingIndex, line.size());

        return StrToInt(GameHistoryLimit);

        file.close();
    }
    else 
    {
        clrscr();
        cout << "An error acoured while opening Config.txt \nPerhaps another program is using it\nPress any key to continue";
        getchar();
    }
}

int getGameHistoryLimit() 
{
    ifstream file ("Config.txt");

    if (file.is_open())
    {
        string line;
        getline(file, line);
        getline(file, line);

        int startingIndex = line.find("=") + 2;
        string GameHistoryLimit = line.substr(startingIndex, line.size());

        return StrToInt(GameHistoryLimit);

        file.close();
    }
    else 
    {
        clrscr();
        cout << "An error acoured while opening Config.txt \nPerhaps another program is using it\nPress any key to continue";
        getchar();
    }
}

int getGameHistoryLimit() 
{
    ifstream file ("Config.txt");

    if (file.is_open())
    {
        string line;
        getline(file, line);
        getline(file, line);

        int startingIndex = line.find("=") + 2;
        string GameHistoryLimit = line.substr(startingIndex, line.size());

        return StrToInt(GameHistoryLimit);

        file.close();
    }
    else 
    {
        clrscr();
        cout << "An error acoured while opening Config.txt \nPerhaps another program is using it\nPress any key to continue";
        getchar();
    }
}

int getGameHistoryLimit() 
{
    ifstream file ("Config.txt");

    if (file.is_open())
    {
        string line;
        getline(file, line);
        getline(file, line);

        int startingIndex = line.find("=") + 2;
        string GameHistoryLimit = line.substr(startingIndex, line.size());

        return StrToInt(GameHistoryLimit);

        file.close();
    }
    else 
    {
        clrscr();
        cout << "An error acoured while opening Config.txt \nPerhaps another program is using it\nPress any key to continue";
        getchar();
    }
}

int getGameHistoryLimit() 
{
    ifstream file ("Config.txt");

    if (file.is_open())
    {
        string line;
        getline(file, line);
        getline(file, line);

        int startingIndex = line.find("=") + 2;
        string GameHistoryLimit = line.substr(startingIndex, line.size());

        return StrToInt(GameHistoryLimit);

        file.close();
    }
    else 
    {
        clrscr();
        cout << "An error acoured while opening Config.txt \nPerhaps another program is using it\nPress any key to continue";
        getchar();
    }
}