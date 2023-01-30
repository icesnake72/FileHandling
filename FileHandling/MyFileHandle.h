#pragma once

#include <stdio.h>
#include <vcruntime_string.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <malloc.h> 


typedef struct {
    short num;      // 사번
    char name[30];  // 이름
    short buseo;    // 부서
    short jikgup;   // 직급
} EMPLOY;

typedef struct {
    short code;
    char buseo_name[20];
}BUSEO_CODE;

typedef struct {
    short code;
    char jikgup_name[20];
}JIKGUP_CODE;

#define CANNOT_OPEN_FILE    0
#define CANNOT_WRITE        -1
#define CANNOT_READ         -2
#define INVALID_CODE        -3
#define CANNOT_SEEK         -4
#define INVALID_PARAM       -5
#define SUCCESS_OPERATION   1

#define FILE_ACR_EMPLOY  0
#define FILE_ACR_BUSEO   1
#define FILE_ACR_JIKGUP  2


#define RW_EMPLOY    1
#define RW_BUSEO     2
#define RW_JIKGUP    3


#define EMPLOY_FILE     "c:\\employ.dat"
#define BUSEO_FILE      "c:\\buseo.dat"
#define JIKGUP_FILE     "c:\\jikgup.dat"

#define FILE_NAME_LEN   512

#define MAX_RECORDS     10
#define MAX_EMP_BUFFER  (sizeof(EMPLOY) * MAX_RECORDS)


void OnFileHandleEvent(void* p, unsigned long size, unsigned int nCode);

int SetFileNameAndDataSize(int nCode, char* szFileName, unsigned short fileNameLen, unsigned long* lSize);

// short WriteToFile(EMPLOY* emp);
short WriteToFile(void* pData, unsigned long lDataSize, int nCode);

// short ReadFromFile(EMPLOY* emp, void (*ptrFileHandler)(void* p, unsigned int nCode), unsigned short toReadCount=10);
//short ReadFromFile(void* pData, int nCode, void (*ptrFileHandler)(void* p, unsigned int nCode), unsigned short toReadCount = 10);
short ReadFromFile(void* pData, unsigned long dataSize, int nCode, void (*ptrFileHandler)(void* p, unsigned long size, unsigned int nCode)=NULL, unsigned short toReadCount=10);

short GetFileSize(const char* filename, unsigned long* size);

void ErrorHandle(short errCode);


short AppendData(void** ppData, unsigned long *lSizeData, void* pAppend, unsigned long lAppendSize);

short ExistFile(const char* filename);