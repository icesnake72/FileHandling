#pragma once
#ifndef ___SHOW_INFO_H___
#define ___SHOW_INFO_H___

#include "FileHandle.h"

void PrintTitle(short mode);

void PrintRecord(short mode, void* pData, size_t empSize, BUSEO_CODE* pbu = NULL, size_t buSize = 0, JIKGUP_CODE* pji = NULL, size_t jiSize = 0);

void PrintEmployeeRecord(void* pData, size_t empSize, BUSEO_CODE* pbu, size_t buSize, JIKGUP_CODE* pji, size_t jiSize);

void PrintBuseoRecord(BUSEO_CODE* pbu, size_t buSize);

void PrintJikgupRecord(JIKGUP_CODE* pji, size_t jiSize);

s_res InputRecord(EMPLOYEE* emp, EMPLOYEE* emps=NULL, size_t lSize=0);

s_res InputBuseo(BUSEO_CODE* code, BUSEO_CODE* pbu=NULL, size_t lSize=0);

s_res UpdateBuseo(BUSEO_CODE* pbu, const size_t lSize);

s_res SearchBuseo(short nCode, BUSEO_CODE* buseo, const size_t lBufSize, const BUSEO_CODE* pbu, const size_t lSize);

s_res InputJikGup(JIKGUP_CODE* code, JIKGUP_CODE* pji=NULL, size_t lSize=0);

s_res GetBuseoName(short nCode, void* pData, size_t lSize, char* name, size_t bufSize);

s_res GetJikgupName(short nCode, void* pData, size_t lSize, char* name, size_t bufSize);

s_res ExistCode(short code, short nMode, void* pData, size_t lSizeData);

void ShowMenu();

void ShowSubMenu();

#endif