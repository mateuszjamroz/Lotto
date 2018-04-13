#include "jackpot.h"
#include "data.h"
#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>    
#include <memory.h>

int AllocAddBet(Bets** BetTab, int nCurrSize);
int AllocAdd(LottoPlayer*** pTab, int nCurrSize);

//-------------------------------------------------------------------

int AllocAdd(LottoPlayer*** pTab, int nCurrSize)
{
	LottoPlayer** pCopyArray = *pTab;
	*pTab = (LottoPlayer**)realloc(*pTab, (NPLAYER + nCurrSize) * sizeof(LottoPlayer*));
	if (!(*pTab))
	{
		printf("Memory not reallocated!");
		*pTab = pCopyArray;
		return 0;
	}
	memset(*pTab + nCurrSize, 0, NPLAYER * sizeof(LottoPlayer*));
	return NPLAYER;
}

int AllocAddBet(Bets** BetTab, int nCurrSize)
{
	Bets* pCopyBet = *BetTab;
	*BetTab = (Bets*)realloc(*BetTab, (BETS + nCurrSize) * sizeof(Bets));
	if (!(*BetTab))
	{
		printf("Memory not reallocated!");
		*BetTab = pCopyBet;
		return 0;
	}
	memset(*BetTab + nCurrSize, 0, BETS * sizeof(Bets));
	return BETS;
}

//-----------------------------------------------------------------
int ReadData(LottoPlayer*** Draws, const char* file)
{
	FILE* fin = NULL;
	if ((fin = fopen(file, "r")) == NULL)
	{
		printf("Cannot open file!");
		return 0;
	}
	int playersnb = 0;
	int MaxSizeTab = 0;
	LottoPlayer** CopyDraws = *Draws;
	char c;
	while (!feof(fin))
	{
		if ((c = fgetc(fin)) == '*')
		{
			if (playersnb == MaxSizeTab)
			{
				MaxSizeTab += AllocAdd(&CopyDraws, playersnb);
				if (playersnb == MaxSizeTab)
					break;
			}
			LottoPlayer* p = CopyDraws[playersnb] = (LottoPlayer*)calloc(1, sizeof(LottoPlayer)); //nastepny gracz
			if (!p)
			{
				printf("Unable to allocate memory!");
				return 0;
			}
			char s;
			int d;
			int m;
			int y;
			Swift* v1 = &(p->NbBank.SwiftNb);
			InBankNumb* v2 = &(p->NbBank.BankNb);
			fscanf(fin, "%s %s %c %8c%3c %2c%2c%8c%16c %d/%d/%d %11c\n", p->sName, p->Name, &s, v1->sBank, v1->sBranch, v2->iCountryID, v2->iControlSum, v2->iBankNb,v2->iAccount, &d, &m, &y, p->PSL);
			
			if (!(SetDate(p, d, m, y)))
			{
				printf("Error in SetDate!");
				return  playersnb;
			}
			if (!(SetSex(p, s)))
			{
				printf("Error in SetSex!");
				return  playersnb;
			}
			
			while ((c = fgetc(fin)) != '*')
			{
				if (feof(fin))
					break;
				ungetc(c, fin);
				if (p->CurrSize == p->MaxSize)
				{
					p->MaxSize += AllocAddBet(&(p->PersonalBets), p->CurrSize);
					if (p->CurrSize == p->MaxSize)
						break;
				}
				int *p5 = p->PersonalBets[p->CurrSize].p50 = (int*)calloc(N1, sizeof(int));
				if (!p5)
				{
					printf("Unable to allocate memory!");
					return 0;
				}
				int* p2 = p->PersonalBets[p->CurrSize].p10 = (int*)calloc(N2, sizeof(int));
				if (!p2)
				{
					printf("Unable to allocate memory!");
					return 0;
				}
				for (int i = 0; i < N1; i++, p5++)
					fscanf(fin, "%d", p5);
				fscanf(fin, "%d %d", p2, p2+1);
				p->CurrSize++;
				fscanf(fin, "\n");
			}
			playersnb++;
			if (c == '*')
				ungetc(c, fin);
		}
	}
	*Draws = CopyDraws;
	fclose(fin);
	return  playersnb;
}


int SetSex(LottoPlayer* p, char c)
{
	/*if (c != 'f' && c != 'F' && c != 'm' && c != 'M')
		return 0;*///!!!!!!!
	switch (c)
	{
	case 'f':
	case 'F': p->pSex = female; return 1;
	case 'm':
	case 'M': p->pSex = male; return 1;
	}
	return 0;
}

int SetDate(LottoPlayer* p, int d, int m, int y)
{
	if (!((d > 0) && (d < 32) && (m > 0) && (m < 13) && (y > 1900)))
		return 0;
	struct tm readTime; //!!!!
	readTime.tm_year = y - 1900;
	readTime.tm_mon = m - 1;
	readTime.tm_mday = d - 1;
	readTime.tm_hour = readTime.tm_min = readTime.tm_sec = 0;
	if (!(mktime(&readTime)))
	{
		printf("ERROR 1");
		return 0;
	}
	
	switch (readTime.tm_wday)
	{
	case 0:p->tBets.nDayWeek = Mon; break;
	case 1:p->tBets.nDayWeek = Tue; break;
	case 2:p->tBets.nDayWeek = Wed; break;
	case 3:p->tBets.nDayWeek = Thu; break;
	case 4:p->tBets.nDayWeek = Fri; break;
	case 5:p->tBets.nDayWeek = Sat; break;
	case 6:p->tBets.nDayWeek = Sun; break;
	}
	switch (m)
	{
	case 1: p->tBets.nMonth = January; break;
	case 2: p->tBets.nMonth = February; break;
	case 3: p->tBets.nMonth = March; break;
	case 4: p->tBets.nMonth = April; break;
	case 5: p->tBets.nMonth = May; break;
	case 6: p->tBets.nMonth = June; break;
	case 7: p->tBets.nMonth = July; break;
	case 8: p->tBets.nMonth = August; break;
	case 9: p->tBets.nMonth = September; break;
	case 10: p->tBets.nMonth = October; break;
	case 11: p->tBets.nMonth = November; break;
	case 12: p->tBets.nMonth = December; break;
	}
	p->tBets.nDay = d;
	p->tBets.nYear = y;
	return 1;
}

void FreeMem(LottoPlayer** pTab, int DrawNb)
{
	for (int i = 0; i < DrawNb; i++)
	{
		LottoPlayer* v = pTab[i];
		Bets* g = v->PersonalBets;
		for (int j = 0; j < v->CurrSize; j++,g++)//!!!!
		{
			free(g->p50);
			free(g->p10);
		}
		free(v->PersonalBets); //!!!!
		free(v);
	}
	free(pTab);
	//pTab = NULL; !!!!
}
