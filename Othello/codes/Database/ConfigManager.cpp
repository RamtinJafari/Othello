#include <iostream>
#include <fstream>
#include "../Utilities/StrToInt.h"
#include "../utilities/IntToStr.h"
#include "ConfigManager.h"

using namespace std;



string getElementOfConfig(int index);
int getGameHistoryLimit();
int getBoardSize();
std::string getBoardColor();
std::string getBoardBorderColor();
bool getSound();
bool getShowAvailablePlacesForPieces();
bool getHint();
int getHintLimit();
void modifyElementOfConfig(int index, string newValue);
void modifyGameHistoryLimit(int);
void modifyBoardSize(int);
void modifyBoardColor(std::string);
void modifyBoardBorderColor(std::string);
void modifySound(bool);
void modifyShowAvailablePlacesForPieces(bool);
void modifyHint(bool);
void modifyHintLimit(int);



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


void modifyElementOfConfig(int index, string newValue)
{
    if (index > 7)
    {
        throw 2; // out of bounds
    }

    std::ifstream fileToRead("Config.txt");
    if (!fileToRead.is_open())
    {
        throw 1; // failed to read the file
    }

    std::string lines[8];

    for (int i{0}; i <= index + 3; i++)
    {
        getline(fileToRead, lines[i]);
    }
    
    fileToRead.close();

    string targetLine = lines[index + 1];
    int startingIndex = targetLine.find("=") + 2;
    targetLine = targetLine.substr(0, startingIndex) + newValue;
    lines[index + 1] = targetLine;

    std::ofstream fileToWrite ("Config.txt");
    if (!fileToWrite.is_open())
    {
        throw 1; // failed to read the file
    }

    for (std::string l : lines)
    {
        fileToWrite << l << std::endl;
    }
    fileToWrite.close();
}


int getGameHistoryLimit() 
{
    return strToInt(getElementOfConfig(0));
}


int getBoardSize() 
{
    return strToInt(getElementOfConfig(1));
}


string getBoardColor() 
{
    return getElementOfConfig(2);
}


string getBoardBorderColor() 
{
    return getElementOfConfig(3);
}


bool getSound() 
{
    int intBool = strToInt(getElementOfConfig(4));
    return static_cast<bool>(intBool);
}


bool getShowAvailablePlacesForPieces() 
{
    int intBool = strToInt(getElementOfConfig(5));
    return static_cast<bool>(intBool);
}


bool getHint() 
{
    int intBool = strToInt(getElementOfConfig(6));
    return static_cast<bool>(intBool);
}


int getHintLimit() 
{
    return strToInt(getElementOfConfig(7));
}


void modifyGameHistoryLimit(int gameHistoryLimit) 
{
    modifyElementOfConfig(0, intToStr(gameHistoryLimit));
}


void modifyBoardSize(int boardSize) 
{
    modifyElementOfConfig(1, intToStr(boardSize));
}


void modifyBoardColor(string color) 
{
    modifyElementOfConfig(2, color);
}


void modifyBoardBorderColor(string color) 
{
    modifyElementOfConfig(3, color);
}


void modifySound(bool sound) 
{
    int sound = static_cast<int>(sound);
    modifyElementOfConfig(4, intToStr(sound));
}


void modifyShowAvailablePlacesForPieces(bool newValue) 
{
    int newValue = static_cast<int>(newValue);
    modifyElementOfConfig(5, intToStr(newValue));
}


void modifyHint(bool hint) 
{
    int hint = static_cast<int>(hint);
    modifyElementOfConfig(6, intToStr(hint));
}


void modifyHintLimit(int hintLimit) 
{
    modifyElementOfConfig(7, intToStr(hintLimit));
}