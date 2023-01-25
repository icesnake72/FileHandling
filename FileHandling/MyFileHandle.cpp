#include <stdio.h>
#include <vcruntime_string.h>
#include <string.h>

#include "MyFileHandle.h"



void ErrorHandle(short errCode)
{
    switch (errCode)
    {
    case CANNOT_OPEN_FILE:
        printf("파일을 열지 못했습니다.\n");
        break;

    case CANNOT_WRITE:
        printf("파일쓰기 실패\n");
        break;
    }
}

void PrintTitle()
{
    printf("사번\t");
    printf("이름\t\t");
    printf("부서코드\t");
    printf("직급코드\n");
    for (int i = 0; i < 50; i++)
        printf("=");

    printf("\n");
}

void PrintRecord(EMPLOY* emp)
{
    /*
    printf("사번 : %d\n", emp->num);
    printf("이름 : %s\n", emp->name);
    printf("부서코드 : %d\n", emp->buseo);
    printf("직급코드 : %d\n", emp->jikgup);
    */

    printf("%d\t", emp->num);
    printf("%s\t\t", emp->name);
    printf("%d\t\t", emp->buseo);
    printf("%d\n", emp->jikgup);
}

short InputRecord(EMPLOY* emp)
{    
    printf("직원 데이터베이스 입력 프로그램입니다\n\n");

    int nRet = 0;
    printf("사번을 입력해주세요\n");
    nRet = scanf_s("%hd", &emp->num);
    if (!nRet) return 0;
    
    printf("직원 이름을 입력해주세요(한글 14자 제한)\n");
    nRet = scanf_s("%29s", emp->name, (unsigned int)sizeof(emp->name));
    if (!nRet) return 0;
        
    printf("부서 코드를 입력해주세요\n");
    nRet = scanf_s("%hd", &emp->buseo);
    if (!nRet) return 0;

    printf("직급 코드를 입력해주세요\n");
    scanf_s("%hd", &emp->jikgup);
    if (!nRet) return 0;

    return 1;
}

int SetFileNameAndDataSize(int nCode, char* szFileName, unsigned short fileNameLen, unsigned short *dataSize)
{
    switch (nCode)
    {
    case RW_EMPLOY:
        strcpy_s(szFileName, FILE_NAME_LEN, EMPLOY_FILE);
        *dataSize = (unsigned short)sizeof(EMPLOY);
        break;

    case RW_BUSEO:
        strcpy_s(szFileName, FILE_NAME_LEN, BUSEO_FILE);
        *dataSize = (unsigned short)sizeof(BUSEO_CODE);
        break;

    case RW_JIKGUP:
        strcpy_s(szFileName, FILE_NAME_LEN, JIKGUP_FILE);
        *dataSize = (unsigned short)sizeof(JIKGUP_CODE);
        break;

    default:
        *dataSize = 0;
        return INVALID_CODE;
    }

    return SUCCESS_OPERATION;
}


// short WriteToFile(EMPLOY* emp)
short WriteToFile(void* pData, int nCode)
{
    unsigned short dataSize = 0;
    char szFileName[FILE_NAME_LEN];
    memset(szFileName, 0, FILE_NAME_LEN);
    if (SetFileNameAndDataSize(nCode, szFileName, FILE_NAME_LEN, &dataSize)== INVALID_CODE)
        return INVALID_CODE;
    
    FILE* fp = NULL;
    fopen_s(&fp, szFileName, "ab");
    if (fp == NULL)
    {        
        return CANNOT_OPEN_FILE;
    }

    // printf("sizeof(EMPLOY)=%zd\n", sizeof(EMPLOY));
    // PrintRecord(emp);

    size_t nRet = 0;
    nRet = fwrite(pData, dataSize, 1, fp);
    if (!nRet)
        return CANNOT_WRITE;

    // (nRet) ? printf("파일쓰기 성공(%zd block(s))\n", nRet) : printf("파일쓰기 실패\n");
    fclose(fp);
    fp = NULL;

    return SUCCESS_OPERATION;
}



// short ReadFromFile(EMPLOY* emp, void (*ptrFileHandler)(void* p, unsigned int nCode), unsigned short toReadCount)
short ReadFromFile(void* pData, int nCode, void (*ptrFileHandler)(void* p, unsigned int nCode), unsigned short toReadCount)
{
    unsigned short dataSize = 0;
    char szFileName[FILE_NAME_LEN];
    memset(szFileName, 0, FILE_NAME_LEN);
    if (SetFileNameAndDataSize(nCode, szFileName, FILE_NAME_LEN, &dataSize) == INVALID_CODE)
        return INVALID_CODE;

    unsigned int readDataCode;
    switch (nCode)
    {
    case RW_EMPLOY: readDataCode = FILE_ACR_EMPLOY; break;
    case RW_BUSEO:  readDataCode = FILE_ACR_BUSEO; break;
    case RW_JIKGUP: readDataCode = FILE_ACR_JIKGUP;
    }


    FILE* fp = NULL;
    fopen_s(&fp, szFileName, "rb");
    if (fp == NULL)
    {
        return CANNOT_OPEN_FILE;
    }

    unsigned short readedCount = 0;
    do {
        size_t nRet = fread_s(pData, dataSize, dataSize, 1, fp);
        if (!nRet)
            return CANNOT_READ;

        ptrFileHandler(pData, readDataCode);
        readedCount++;

    } while (!feof(fp) || readedCount < toReadCount);
    

    fclose(fp);
    fp = NULL;

    return SUCCESS_OPERATION;
}


short InputBuseo(BUSEO_CODE *code)
{
    printf("부서 기초 정보를 입력해주세요\n\n");

    int nRet = 0;
    printf("부서 코드를 입력해주세요\n");
    nRet = scanf_s("%hd", &code->code);
    if (!nRet) return 0;

    printf("부서 이름을 입력해주세요(한글 14자 제한)\n");
    nRet = scanf_s("%19s", code->buseo_name, (unsigned int)sizeof(code->buseo_name));
    if (!nRet) return 0;
        
    return 1;
}

short InputJikGup(JIKGUP_CODE *code)
{
    printf("직급 기초 정보를 입력해주세요\n\n");

    int nRet = 0;
    printf("직급 코드를 입력해주세요\n");
    nRet = scanf_s("%hd", &code->code);
    if (!nRet) return 0;

    printf("직급 이름을 입력해주세요(한글 14자 제한)\n");
    nRet = scanf_s("%19s", code->jikgup_name, (unsigned int)sizeof(code->jikgup_name));
    if (!nRet) return 0;

    return 1;
}