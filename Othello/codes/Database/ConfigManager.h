#pragma once

#include <string>

int getGameHistoryLimit();
int getBoardSize();
std::string getBoardColor();
std::string getBoardBorderColor();
bool getSound();
bool getShowAvailablePlacesForPieces();
bool getHint();
int getHintLimit();

void modifyGameHistoryLimit(int);
void modifyBoardSize(int);
void modifyBoardColor(std::string);
void modifyBoardBorderColor(std::string);
void modifySound(bool);
void modifyShowAvailablePlacesForPieces(bool);
void modifyHint(bool);
void modifyHintLimit(int);