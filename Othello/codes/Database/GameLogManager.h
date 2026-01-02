#pragma once

#include "../Structures/Move.h"

void clearGameLog();
void addLog(Move move);
int countLogs();
Move getLog(int logIndex);