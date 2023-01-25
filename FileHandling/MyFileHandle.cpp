#include <stdio.h>

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

void PrintRecord(EMPLOY* emp)
{
    printf("사번 : %d\n", emp->num);
    printf("이름 : %s\n", emp->name);
    printf("부서코드 : %d\n", emp->buseo);
    printf("직급코드 : %d\n", emp->jikgup);
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


short WriteToFile(EMPLOY* emp)
{
    FILE* fp = NULL;
    fopen_s(&fp, "c:\\employ.dat", "wb");
    if (fp == NULL)
    {        
        return CANNOT_OPEN_FILE;
    }

    printf("sizeof(EMPLOY)=%zd\n", sizeof(EMPLOY));
    PrintRecord(emp);

    size_t nRet = 0;
    nRet = fwrite(emp, sizeof(EMPLOY), 1, fp);
    if (!nRet)
        return CANNOT_WRITE;

    // (nRet) ? printf("파일쓰기 성공(%zd block(s))\n", nRet) : printf("파일쓰기 실패\n");
    fclose(fp);
    fp = NULL;

    return SUCCESS_OPERATION;
}

short ReadFromFile(EMPLOY* emp)
{
    FILE* fp = NULL;
    fopen_s(&fp, "c:\\employ.dat", "rb");
    if (fp == NULL)
    {
        return CANNOT_OPEN_FILE;
    }

    size_t nRet = fread_s(emp, sizeof(EMPLOY), sizeof(EMPLOY), 1, fp);
    if (!nRet)
        return CANNOT_READ;

    fclose(fp);
    fp = NULL;

    return SUCCESS_OPERATION;

}