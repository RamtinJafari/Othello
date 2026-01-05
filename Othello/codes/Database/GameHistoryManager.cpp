// a saved game will follow this patter:
//  [gameId][.|.|.|.][1Player][PlayerName|PlayerColor][BotName or PlayerName|BotColor or PlayerColor]['B'][0] and winner at the end
//          GameBoard   mode          Player1                       Player2 or Bot                current turn

#include "../Structures/Config.h"
#include "../Structures/SinglePlayerGame.h"
#include "../Structures/MultiPlayerGame.h"
#include "../Utilities/StrToInt.h"
#include "../Utilities/IntSqrt.h"
#include "../Utilities/StrToSymbol.h"
#include "GameHistoryManager.h"
#include <fstream>

// file managing
void writeTempoToGameHistory(); 
void updateLine(int lineIndex, std::string str); 
void addLine(std::string str); 
void freeLastLine(); 

// internal uses
int getLinesCount(); 
std::string getProperty(int propertyId, std::string game);
int getGameId(std::string game); 
int getSavedBoardElementCount(std::string board); 

// adding data
void saveGame(SinglePlayerGame* game);
void saveGame(MultiPlayerGame* game);

// extracting data
std::string getGameById(int gameId);
int getLineIndexById(int gameId); 
std::string getLineByLineIndex(int lineIndex);

// external uses
SinglePlayerGame getSinglePlayerGame(int id);
MultiPlayerGame getMultiPlayerGame(int id);
void syncGameHistoryWithLimit();
int getFirstGameId();
int getLastGameId();


//----------------------------------- file managing --------------------------------------------------------------
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
        GameHistoryToWrite << line << "\n";
    }

    tempoFileToRead.close();
    GameHistoryToWrite.close();
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
        tempoFileToWrite << line << "\n";
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
            tempoFileToWrite << line << "\n";
        }
        curLineIndex++;
    }

    tempoFileToWrite.close();
    GameHistoryToRead.close();

    writeTempoToGameHistory();
}


void addLine(std::string str)
{
    std::ofstream GameHistory("GameHistory.txt", std::ios::app);

    GameHistory << str << "\n";

    GameHistory.close();
}



//----------------------------------- internal use -----------------------------------------------
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
}


std::string getProperty(int propertyId, std::string game)
{
    for (int i = 0; i < propertyId; i++)
    {
        int endingIndex = game.find("]");
        game = game.substr(endingIndex + 1, game.size());
    }

    int EndingIndex = game.find("]");
    std::string property = game.substr(
        1, EndingIndex - 1
    );

    return property;
}


int getGameId(std::string game)
{
    return strToInt(getProperty(0, game));
}


void syncGameHistoryWithLimit()
// has to be called when limit changes, so GameHistory.txt stays within its new limit
{
    int curCount = getLinesCount();
    int limit = Config::getInstance() -> GAME_HISTORY_LIMIT;

    if (curCount > limit)
    {
        int toRemove = curCount - limit;

        for (int i = 0; i < toRemove; i++)
        {
            freeLastLine();
        }
    }
}


int getSavedBoardElementCount(std::string board)
{
    int count = 0;

    for (char element : board)
    {
        if (element == '|') count++;
    }

    return count + 1;
}


//--------------------------------------------- adding data --------------------------------------------------
void saveGame(SinglePlayerGame* game)
{
    int thisGameId = game -> id;
    std::string gameToSave = game -> retrieveGame();

    int lineIndex = getLineIndexById(thisGameId);

    if (lineIndex == -1)
    {
        addLine(gameToSave);
        syncGameHistoryWithLimit();
    }
    else
    {
        updateLine(lineIndex, gameToSave);
    }
}


void saveGame(MultiPlayerGame* game)
{
    int thisGameId = game -> id;
    std::string gameToSave = game -> retrieveGame();

    int lineIndex = getLineIndexById(thisGameId);

    if (lineIndex == -1)
    {
        addLine(gameToSave);
        syncGameHistoryWithLimit();
    }
    else
    {
        updateLine(lineIndex, gameToSave);
    }
}

//--------------------------------------------- extraxting data --------------------------------------------------
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

    int linesCount = getLinesCount();
    for (int i = 0; i < linesCount; i++)
    {
        getline(fileToRead, line);
        if (i == lineIndex) return line;
    }

    return "";
}
//-------------------------------------------- external uses -----------------------------------------
int getFirstGameId()
{
    int liensCount = getLinesCount();

    if (liensCount == 0) return -1; // file is empty

    std::string game = getLineByLineIndex(0);
    return getGameId(game);
}

int getLastGameId()
{
    int liensCount = getLinesCount();

    if (liensCount == 0) return -1; // file is empty

    std::string game = getLineByLineIndex(liensCount - 1);
    return getGameId(game);
}


SinglePlayerGame getSinglePlayerGame(int id)
{
    std::string savedGame = getGameById(id);
    
    std::string savedBoard = getProperty(1, savedGame);
    int boardSize = intSqrt(
        getSavedBoardElementCount(savedBoard)
    );
    Board board {boardSize};
    board.loadBoard(savedBoard);

    Player player {"", 0};
    player.loadPlayer(getProperty(3, savedGame));

    Bot bot {"", 0};
    bot.loadBot(getProperty(4, savedGame));

    char turn = strToSymbol(getProperty(5, savedGame));

    SinglePlayerGame game {&board, &player, &bot, turn};

    game.id = id;

    return game;
}


MultiPlayerGame getMultiPlayerGame(int id)
{
    std::string savedGame = getGameById(id);
    
    std::string savedBoard = getProperty(1, savedGame);
    int boardSize = intSqrt(
        getSavedBoardElementCount(savedBoard)
    );
    Board board {boardSize};
    board.loadBoard(savedBoard);

    Player player1 {"", 0};
    player1.loadPlayer(getProperty(3, savedGame));

    Player player2 {"", 0};
    player2.loadPlayer(getProperty(4, savedGame));

    char turn = strToSymbol(getProperty(5, savedGame));

    MultiPlayerGame game {&board, &player1, &player2, turn};

    game.id = id;

    return game;
}