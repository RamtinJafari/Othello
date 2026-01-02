#pragma once

#include <string>

// working with GameHistory.txt
void syncWithNewLimit();
int getFirstGameId();
int getLastGameId();
int countUnfinishedGames();
std::string getUnfinishedGame(int number);
void saveGame(std::string game);
std::string getGameById(int gameId);

// working with Game's properties
int getSavedBoardElementCount(std::string board);
int getGameId(std::string game);
std::string getGameBoard(std::string game);
std::string getMode(std::string game);
std::string getPlayer1(std::string game);
std::string getPlayer2(std::string game);
std::string getBot(std::string game);
char getCurrentTurnColor(std::string game);
int getWinner(std::string game);