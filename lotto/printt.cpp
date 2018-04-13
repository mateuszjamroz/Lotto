#include "print.h"
#include "data.h"
#include "jackpot.h"
#include <stdio.h>
#include <string.h>


void PrintSex(FILE* fout, LottoPlayer* p);
void PrintData(FILE* fout, LottoPlayer* p);
void PrintBets(FILE* fout, Bets** pBets);

//----------------------------------------

void PrintSex(FILE* fout, LottoPlayer* p)
{
	int length = strlen(p->Name) + strlen(p->sName) + 1;
	for (int i = 0; i < SPACE - length; i++)
		fprintf(fout, " ");
	switch (p->pSex)
	{
	case female: fprintf(fout, "Kobieta\t"); break;
	case male: fprintf(fout, "Mezczyzna\t"); break;
	}
}

void PrintData(FILE* fout, LottoPlayer* p)  //!!!!
{
	switch (p->tBets.nDayWeek)
	{
	case Mon: fprintf(fout, "Monday "); break;
	case Tue: fprintf(fout, "Tuesday "); break;
	case Wed: fprintf(fout, "Wednesday "); break;
	case Thu: fprintf(fout, "Thursday "); break;
	case Fri: fprintf(fout, "Friday "); break;
	case Sat: fprintf(fout, "Saturday "); break;
	case Sun: fprintf(fout, "Sunday "); break;
	}
	fprintf(fout, "%2d", p->tBets.nDay);
	switch (p->tBets.nMonth)
	{
	case January: fprintf(fout, "/January/"); break;
	case February: fprintf(fout, "/February/"); break;
	case March: fprintf(fout, "/March/"); break;
	case April: fprintf(fout, "/April/"); break;
	case May: fprintf(fout, "/May/"); break;
	case June: fprintf(fout, "/June/"); break;
	case July: fprintf(fout, "/July/"); break;
	case August: fprintf(fout, "/August/"); break;
	case September: fprintf(fout, "/September/"); break;
	case October: fprintf(fout, "/October/"); break;
	case November: fprintf(fout, "/November/"); break;
	case December: fprintf(fout, "/December/"); break;
	}
	fprintf(fout, "%4d", p->tBets.nYear);
}

void PrintBets(FILE* fout, Bets** pBets)
{
	int* p5 = (*pBets)->p50;
	int* p2 = (*pBets)->p10;
	fprintf(fout, "\n");
	for (int i = 0; i < N1; i++, p5++)
		fprintf(fout, "%2d ", *p5);
	fprintf(fout, " ");
	for (int j = 0; j < N2; j++, p2++)
		fprintf(fout, "%2d ", *p2);
}

void PrintResults(int* p0, int* p1, LottoPlayer** pDraws, int DrawsNb, char* file)
{
	FILE* fout = NULL;
	if ((fout = fopen(file, "w")) == NULL)
	{
		printf("Cannot open file!");
		return;
	}
	for (int i = 0; i < DrawsNb; i++, pDraws++)
	{
		fprintf(fout, "%s ", (*pDraws)->sName);
		fprintf(fout, "%s ", (*pDraws)->Name);
		PrintSex(fout, *pDraws);
		PrintData(fout, *pDraws);
		LottoPlayer* p = *pDraws;
		Swift* v1 = &(p->NbBank.SwiftNb);
		InBankNumb* v2 = &(p->NbBank.BankNb);
		fprintf(fout, "\t %.8s%.3s %.2s%.2s%.8s%.16s %.11s", v1->sBank, v1->sBranch, v2->iCountryID, v2->iControlSum, v2->iBankNb, v2->iAccount, p->PSL);
		Bets* bet = (*pDraws)->PersonalBets;
		for (int j = 0; j < (*pDraws)->CurrSize - 1; j++, bet++)
			PrintBets(fout, &bet);
		fprintf(fout, "\n--------------------------------------------------------------------------------------\n");
	}
	fprintf(fout, "\nS T A T I S T I C S \n");
	for (int i =1; i < LIMIT+1; i++) //!!
	{
		fprintf(fout, "%2d: %2d ", i, *p0++); //!!
		if (i % 10 == 0)
			fprintf(fout, "\n");
	}
	fprintf(fout, "\n\n");
	for (int j = 1; j < LIMIT2+1; j++)
	{
		fprintf(fout, "%2d: %2d ", j, *p1++); //!!
		if (j % 5 == 0)
			fprintf(fout, "\n");
	}
	fclose(fout);
}