// lotto.cpp : Defines the entry point for the console application.
//
#include "data.h"
#include "jackpot.h"
#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>

void InitTab(int** pBets, int nSize);
void HeapCheck();
void Stat(int* p0, int* p1, LottoPlayer** pDraws, int DrawsNb);
void Sort(LottoPlayer** pDraws, int DrawsNb);
int Comp(char *s1, char* s2);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("There is no input or output file!");
		return 0;
	}
	LottoPlayer** players = NULL;
	int readnb;
	if (!(readnb = ReadData(&players, argv[1])))
	{
		printf("Cannot read data!");
		return 2;
	}
	int* pBets1 = NULL;
	int* pBets2 = NULL;
	InitTab(&pBets1, LIMIT + 1);
	InitTab(&pBets2, LIMIT2 + 1);
	Sort(players, readnb);
	Stat(pBets1, pBets2, players, readnb);
	PrintResults(pBets1, pBets2, players, readnb, argv[2]);
	FreeMem(players, readnb);
	HeapCheck();
	return 0;
}

//--------------------------------------------------
void InitTab(int** pBets, int nSize)
{
	*pBets = (int*)calloc(nSize, sizeof(int));
	if (!(*pBets))
	{
		printf("Unable to allocate memory!");
		return;
	}
}

void HeapCheck()
{
	int heapstatus;
	//char* buffer;!!!!!!
	//if ((buffer = (char*)malloc(100)) != NULL)
	//	free(buffer);
	heapstatus = _heapchk();
	switch (heapstatus)
	{
	case _HEAPOK:
		printf(" OK - heap is fine\n");
		break;
	case _HEAPEMPTY:
		printf(" OK - heap is empty\n");
		break;
	case _HEAPBADBEGIN:
		printf("ERROR - bad start of heap\n");
		break;
	case _HEAPBADNODE:
		printf("ERROR - bad node in heap\n");
		break;
	}
}

void Stat(int* p0, int* p1, LottoPlayer** pDraws, int DrawsNb)
{
	int* p50 = p0;
	int* p10 = p1;
	for (int i = 0; i < DrawsNb; i++)
	{
		LottoPlayer* p1 = pDraws[i]; //player
		Bets* p2 = pDraws[i]->PersonalBets; //player bets
		for (int j = 0; j < p1->CurrSize; j++, p2++)
		{
			int* pArray5 = p2->p50;
			for (int k = 0; k < N1; pArray5++, k++)
			{
				if ((*pArray5 < 1) || (*pArray5 > LIMIT))
				{
					printf("Error 2!");
					return;
				}
				p50[*pArray5 - 1]++;
			}
			int* pArray2 = p2->p10;
			for (int k = 0; k < N2; k++,pArray2++)
			{
				if (*pArray2 < 1 || *pArray2 > LIMIT2)
				{
					printf("Error 3!");
					return;
				}
				p10[*pArray2 - 1]++;
			}
		}
	}
}

void Sort(LottoPlayer** pDraws, int DrawsNb)
{
	LottoPlayer** temp = pDraws;
	for (int i = 0; i < DrawsNb; i++)
	{
		LottoPlayer* x = temp[i];
		int ix = i;
		for (int j = i + 1; j < DrawsNb; j++)
		{
			if (!(Comp(temp[j]->sName, temp[ix]->sName)))
			{
				if(Comp(temp[j]->Name, temp[ix]->Name)<0)
				{
					x = temp[j];
					ix = j;
				}
			}
			else if (Comp(temp[j]->sName, temp[ix]->sName) < 0)
			{
				x = temp[j];
				ix = j;
			}
		}
		temp[ix] = temp[i];
		temp[i] = x;
	}
}

int Comp(char *s1, char* s2)
{
	char* Tmp1 = (char*)calloc(1, (strlen(s1) + 1) * sizeof(char));
	if (!Tmp1)
	{
		printf("Unable to allocate memory");
		return 0;
	}
	strcpy(Tmp1, s1);
	char* Tmp2 = (char*)calloc(1, (strlen(s2) + 1) * sizeof(char));
	if (!Tmp2)
	{
		printf("Unable to allocate memory");
		return 0;
	}
	strcpy(Tmp2, s2);
	_strlwr(Tmp1); //lowercase
	_strlwr(Tmp2);
	int res = strcmp(Tmp1, Tmp2); // >0 ; 0 ; <0
	free(Tmp1);
	free(Tmp2);
	return res;
	
}