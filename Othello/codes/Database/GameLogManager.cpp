#include "../Structures/Move.h"
#include <fstream>
#include <string>



void clearGameLog();
void addLog(Move move);
int countLogs();
Move getLog(int logIndex);



void clearGameLog()
{
    std::ofstream file ("GameLog.txt", std::ios::trunc);
    if (!file.is_open())
    {
        throw 1; // failed to read file
    }

    file.close();
}


void addLog(Move move)
{
    std::ofstream file("GameLog.txt", std::ios::app);
    if (!file.is_open())
    {
        throw 1; // failed to read file
    }

    file << move.retrieveMove() << "\n";

    file.close();
}


int countLogs()
{
    int logCount = 0;
    std::ifstream file("GameLog.txt");
    std::string line;

    while(std::getline(file, line))
    {
        if (line.empty()) continue;

        logCount++;
    }

    return logCount;
}


Move getLog(int logIndex)
{
    std::ifstream file ("Config.txt");
    if (!file.is_open())
    {
        throw 1; // failed to read the file
    }

    std::string line;

    for (int i{0}; i <= logIndex; i++)
    {
        std::getline(file, line);
    }

    Move move{0, 0, '0'};
    
    move.loadMove(line);

    return move;
}