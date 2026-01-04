#include "../Utilities/StrToInt.h"
#include "../Structures/Config.h"
#include <iostream>
#include <fstream>


void writeTempoToGameHistory();
void addLineToEnd(std::string str);
void freeLastLine();
void updateLine(int lineIndex, std::string str);
int getLineIndexById(int gameId);
std::string getLineByLineIndex(int lineIndex);
void saveGame(std::string game);
int getLinesCount();
void syncWithNewLimit();
int getFirstGameId();
int getLastGameId();
int countUnfinishedGames();
std::string getUnfinishedGame(int number);
std::string getGameById(int gameId);
std::string getProperty(int id, std::string game);
int getSavedBoardElementCount(std::string board);
int getGameId(std::string game);
std::string getGameBoard(std::string game);
std::string getMode(std::string game);
std::string getPlayer1(std::string game);
std::string getPlayer2(std::string game);
std::string getBot(std::string game);
char getCurrentTurnColor(std::string game);
int getWinner(std::string game);



//----------------------------------- working with GameHistory.txt -----------------------------------------------
void syncWithNewLimit()
// has to be called when the game starts to be updated with config's confidurations
{
    int curCount = getLinesCount();
    int limit = Config::getInstance() -> GAME_HISTORY_LIMIT;

    if (curCount > limit)
    {
        int toRemove = curCount - limit;

        std::ifstream GameHistoryToRead("codes/Database/GameHistory.txt");
        std::ofstream tempoFileToWrite("codes/Database/tempo.txt");

        if (!GameHistoryToRead.is_open() && !tempoFileToWrite.is_open())
        {
            throw 1; // faild to read file
        }
        
        std::string line;

        for (int i = 0; i < toRemove; i++)
        {
            getline(GameHistoryToRead, line); // skipping lines
        }

        while (getline(GameHistoryToRead, line))
        {
            tempoFileToWrite << line;
        }

        tempoFileToWrite.close();
        GameHistoryToRead.close();

        writeTempoToGameHistory();
    }
}


int countUnfinishedGames()
{
    int count = 0;

    std::string line;
    std::ifstream fileToRead("codes/Database/GameHistory.txt");

    if (!fileToRead.is_open())
    {
        throw 1; // faild to read file
    }

    while (getline(fileToRead, line))
    {
        if (getWinner(line) == 0) count++;
    }

    return count;
}


std::string getUnfinishedGame(int index)
{
    int curIndex = 0;

    std::string line;
    std::ifstream fileToRead("codes/Database/GameHistory.txt");

    if (!fileToRead.is_open())
    {
        throw 1; // faild to read file
    }

    while (getline(fileToRead, line))
    {
        if (getWinner(line) == 0)
        {
            if (curIndex == index) break;
            curIndex++;
        }
    }

    return line;
}


int getFirstGameId()
{
    int maxIndex = getLinesCount() - 1;

    if (maxIndex == 0) return -1; // file is empty
    if (maxIndex == 0) return 0; // only one game

    std::string game = getLineByLineIndex(0);
    return getGameId(game);
}

int getLastGameId()
{
    int maxIndex = getLinesCount() - 1;

    if (maxIndex == -1) return -1; // file is empty
    if (maxIndex == 0) return 0; // only one game

    std::string game = getLineByLineIndex(maxIndex);
    return getGameId(game);
}


int getLinesCount()
{
    int count = 0;

    std::string line;
    std::ifstream fileToRead("codes/Database/GameHistory.txt");

    if (!fileToRead.is_open())
    {
        throw 1; // faild to read file
    }

    while (getline(fileToRead, line))
    {
        if (!line.empty()) count++;
    }

    return count;
    // there is a newline at the end of the GameHistory.txt
}


void writeTempoToGameHistory()
{
    std::ifstream tempoFileToRead("codes/Database/tempo.txt");
    std::ofstream GameHistoryToWrite("codes/Database/GameHistory.txt");

    if (!GameHistoryToWrite.is_open() && !tempoFileToRead.is_open())
    {
        throw 1; // faild to read file
    }
    
    std::string line;

    while (getline(tempoFileToRead, line))
    {
        GameHistoryToWrite << line;
    }

    tempoFileToRead.close();
    GameHistoryToWrite.close();
}


void addLineToEnd(std::string str)
{
    std::ofstream file("codes/Database/GameHistory.txt", std::ios::app);

    if (!file.is_open())
    {
        throw 1; // faild to read file
    }

    file << str << "\n";

    file.close();
}


void freeLastLine()
{
    std::ifstream GameHistoryToRead("codes/Database/GameHistory.txt");
    std::ofstream tempoFileToWrite("codes/Database/tempo.txt");

    if (!GameHistoryToRead.is_open() && !tempoFileToWrite.is_open())
    {
        throw 1; // faild to read file
    }
    
    std::string line;

    getline(GameHistoryToRead, line); // skipping the first line

    while (getline(GameHistoryToRead, line))
    {
        tempoFileToWrite << line;
    }

    tempoFileToWrite.close();
    GameHistoryToRead.close();

    writeTempoToGameHistory();
}


void updateLine(int lineIndex, std::string str)
{
    std::ifstream GameHistoryToRead("codes/Database/GameHistory.txt");
    std::ofstream tempoFileToWrite("codes/Database/tempo.txt");

    if (!GameHistoryToRead.is_open() && !tempoFileToWrite.is_open())
    {
        throw 1; // faild to read file
    }
    
    int curLineIndex = 0;
    std::string line;

    while (getline(GameHistoryToRead, line))
    {
        if (curLineIndex == lineIndex)
        {
            tempoFileToWrite << str << "\n";
        }
        else
        {
            tempoFileToWrite << line;
        }
        curLineIndex++;
    }

    tempoFileToWrite.close();
    GameHistoryToRead.close();

    writeTempoToGameHistory();
}


int getLineIndexById(int gameId)
{
    std::string line;
    std::ifstream fileToRead("codes/Database/GameHistory.txt");

    if (!fileToRead.is_open())
    {
        throw 1; // faild to read file
    }

    int id = 0;
    while (getline(fileToRead, line))
    {
        if (getGameId(line) == gameId)
        {
            return id;
        }
        id++;
    }

    return -1;
}


std::string getLineByLineIndex(int lineIndex)
{
    std::string line;
    std::ifstream fileToRead("codes/Database/GameHistory.txt");

    if (!fileToRead.is_open())
    {
        throw 1; // faild to read file
    }

    int maxIndex = getLinesCount() - 1;
    for (int i = 0; i < maxIndex; i++)
    {
        if (i == lineIndex) return line;
    }

    return "";
}


void saveGame(std::string game)
{
    int thisGameId = getGameId(game);

    int lineIndex = getLineIndexById(thisGameId);

    if (lineIndex == -1)
    {
        if (getLinesCount() == Config::getInstance() -> GAME_HISTORY_LIMIT) // reached the limit
        {
            freeLastLine();
        }
        addLineToEnd(game);
    }
    else
    {
        updateLine(lineIndex, game);
    }
}


std::string getGameById(int gameId)
{
    std::string line;
    std::ifstream fileToRead("codes/Database/GameHistory.txt");

    if (!fileToRead.is_open())
    {
        throw 1; // faild to read file
    }

    while (getline(fileToRead, line))
    {
        if (getGameId(line) == gameId)
        {
            return line;
        }
    }

    return "";
}


//---------------------------------------- working with Game properties --------------------------------------------
int getSavedBoardElementCount(std::string board)
{
    int count = 0;

    for (char element : board)
    {
        if (element == '|') count++;
    }

    return count + 1;
}

std::string getProperty(int id, std::string game)
{
    for (int i = 0; i < id; i++)
    {
        int EndingIndex = game.find("]");
        game = game.substr(
            EndingIndex + 1
        );
    }

    int EndingIndex = game.find("]");
    return game.substr(
        1, EndingIndex
    );
}


int getGameId(std::string game)
{
    return strToInt(getProperty(0, game));
}


std::string getGameBoard(std::string game)
{
    return getProperty(1, game);
}


std::string getMode(std::string game)
{
    return getProperty(2, game);
}


std::string getPlayer1(std::string game)
{
    return getProperty(3, game);
}


std::string getPlayer2(std::string game)
{
    return getProperty(4, game);
}


std::string getBot(std::string game)
{
    return getProperty(4, game);
}


char getCurrentTurnColor(std::string game)
{
    return (char) getProperty(5, game)[0];
}


int getWinner(std::string game)
{
    return strToInt(getProperty(6, game));
}