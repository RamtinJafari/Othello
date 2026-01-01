#include <iostream>
#include <fstream>
#include "../Utilities/StrToInt.h"
#include "ConfigManager.h"

using namespace std;


string getElementOfConfig(int index)
{
    if (index > 7)
    {
        throw 2; // out of bond
    }

    ifstream file ("Config.txt");
    if (!file.is_open())
    {
        throw 1; // failed to read the file
    }

    string line;

    for (int i{0}; i <= index + 1; i++)
    {
        getline(file, line);
    }

    int startingIndex = line.find("=") + 2;
    string result = line.substr(startingIndex, line.size());

    file.close();

    return result;
}


string modifyElementOfConfig(int index, string newValue)
{
    if (index > 7)
    {
        throw 2; // out of bounds
    }

    ifstream file("Config.txt");
    if (!file.is_open())
    {
        throw 1; // failed to read the file
    }

    string[8] lines;

    for (int i{0}; i <= index + 3;)
    {
        lines[i] = getline(file, line);
    }
    
    file.close();

    string targetLine = lines[index + 1];
    int startingIndex = targetLine.find("=") + 2;
    targetLine = line.substr(0, startingIndex) + newValue;
    lines[index + 1] = targetLine;

    ofstream file ("Config.txt")
    if (!file.is_open())
    {
        throw 1; // failed to read the file
    }

    for (l : lines)
    {
        file << l << endl;
    }
    file.close();
}


int getGameHistoryLimit() 
{
    return StrToInt::strToInt(getElementOfConfig(0));
}


int getBoardSize() 
{
    return StrToInt::strToInt(getElementOfConfig(1));
}


string getBoardColor() 
{
    return getElementOfConfig(2)
}


string getBoardBorderColor() 
{
    return getElementOfConfig(3)
}


bool getSound() 
{
    int intBool = StrToInt::strToInt(getElementOfConfig(4));
    return static_cast<bool>(intBool);
}


bool getShowAvailablePlacesForPieces() 
{
    int intBool = StrToInt::strToInt(getElementOfConfig(5));
    return static_cast<bool>(intBool);
}


bool getHint() 
{
    int intBool = StrToInt::strToInt(getElementOfConfig(6));
    return static_cast<bool>(intBool);
}


int getHintLimit() 
{
    return StrToInt::strToInt(getElementOfConfig(7));
}


void modifyGameHistoryLimit(int gameHistoryLimit) 
{
    modifyElementOfConfig(0, static_cast<string>(gameHistoryLimit));
}


void modifyBoardSize(int boardSize) 
{
    modifyElementOfConfig(1, static_cast<string>(boardSize));
}


void modifyBoardColor(string color) 
{
    return modifyElementOfConfig(2, color)
}


void modifyBoardBorderColor(string color) 
{
    return modifyElementOfConfig(3, color)
}


void modifySound(bool sound) 
{
    int sound = static_cast<int>(sound);
    modifyElementOfConfig(4, static_cast<string>(sound));
}


void modifyShowAvailablePlacesForPieces(bool newValue) 
{
    int newValue = static_cast<int>(newValue);
    modifyElementOfConfig(5, static_cast<string>(newValue));
}


void modifyHint(bool hint) 
{
    int hint = static_cast<int>(hint);
    modifyElementOfConfig(6, static_cast<string>(hint));
}


void modifyHintLimit(int hintLimit) 
{
    modifyElementOfConfig(7, static_cast<string>(hintLimit));
}