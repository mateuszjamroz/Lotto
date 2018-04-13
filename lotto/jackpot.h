#pragma once
#include "data.h"

int ReadData(LottoPlayer*** Draws,const char* file);
int SetSex(LottoPlayer* p, char c);
int SetDate(LottoPlayer* p, int d, int m, int y);
void FreeMem(LottoPlayer** pTab, int DrawNb);