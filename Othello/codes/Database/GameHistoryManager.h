#pragma once

#include <string>
#include "../Structures/MultiPlayerGame.h"
#include "../Structures/SinglePlayerGame.h"

void saveGame(SinglePlayerGame* game);
void saveGame(MultiPlayerGame* game);
SinglePlayerGame getSinglePlayerGame(int id);
MultiPlayerGame getMultiPlayerGame(int id);
void syncGameHistoryWithLimit();
std::string getProperty(int propertyId, std::string game);
int getGameId(std::string game);
int getFirstGameId();
int getLastGameId();