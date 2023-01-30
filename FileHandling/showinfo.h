#pragma once
#ifndef ___SHOW_INFO_H___
#define ___SHOW_INFO_H___

#include "MyFileHandle.h"

void PrintTitle(short mode);

void PrintRecord(short mode, void* pData, long empSize, BUSEO_CODE* pbu = NULL, long buSize = 0, JIKGUP_CODE* pji = NULL, long jiSize = 0);

void PrintEmployRecord(void* pData, long empSize, BUSEO_CODE* pbu, long buSize, JIKGUP_CODE* pji, long jiSize);

void PrintBuseoRecord(BUSEO_CODE* pbu, unsigned long buSize);

void PrintJikgupRecord(JIKGUP_CODE* pji, unsigned long jiSize);

short InputRecord(EMPLOY* emp, EMPLOY* emps=NULL, unsigned long lSize=0);

short InputBuseo(BUSEO_CODE* code);

short InputJikGup(JIKGUP_CODE* code);

short GetBuseoName(short nCode, void* pData, long lSize, char* name, long bufSize);

short GetJikgupName(short nCode, void* pData, long lSize, char* name, long bufSize);

short ExistCode(short code, short nMode, void* pData, unsigned long lSizeData);

void ShowMenu();

void ShowSubMenu();

#endif