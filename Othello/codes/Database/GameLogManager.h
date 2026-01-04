#pragma once

#include "codes/Structures/Move.h"

void clearGameLog();
void addLog(Move move);
int countLogs();
Move getLog(int logIndex);