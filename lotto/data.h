#pragma once
#define COUNTRYID 2
#define CONTROLSUM 2
#define INSTITUTIONNR 4
#define BRANCHNR 3
#define CONTROLNR 1
#define ACCOUNTNR 16
#define SWIFTBANK 8
#define SWIFTBRANCH 3
#define PESEL 11
#define LIMIT 50
#define LIMIT2 10
#define NPLAYER 7
#define MAX 12
#define N1 5
#define N2 2
#define SPACE 20
#define BETS 3

typedef enum {Mon,Tue,Wed,Thu,Fri,Sat,Sun}Day;
typedef enum {January=1,February=25,March,April,May,June,July,August,September,October,November,December}Month;
typedef enum {male,female}Sex;

typedef struct
{
	Month nMonth;
	Day nDayWeek;
	int nDay;
	int nYear;
}Time;

typedef struct
{
	char iCountryID[COUNTRYID];
	char iControlSum[CONTROLSUM];
	char iBankNb[INSTITUTIONNR + BRANCHNR + CONTROLNR];
	char iAccount[ACCOUNTNR];
}InBankNumb;

typedef struct
{
	char sBank[SWIFTBANK];
	char sBranch[SWIFTBRANCH];
}Swift;

typedef struct
{
	InBankNumb BankNb;
	Swift SwiftNb;
}Bank;

typedef struct
{
	int* p50;
	int* p10;
}Bets;

typedef struct
{
	char Name[MAX+1];
	char sName[MAX+1];
	char PSL[PESEL];
	int MaxSize;
	int CurrSize;
	Bets* PersonalBets;
	Bank NbBank;
	Time tBets;
	Sex pSex;
}LottoPlayer;



