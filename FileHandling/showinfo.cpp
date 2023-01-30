//
// 2023년 1월 30일, Coded by E.B Kim
//
// 초간단 인사관리에서 메뉴 및 정보 디스플레이 관련 함수들
//
// 라이선스 없음(무제한 라이선스)



#include "showinfo.h"


void ShowMenu()
{
    system("cls");

    printf("1. 직원 정보 보기\n");
    printf("2. 직원 정보 입력\n");
    printf("3. 직원 정보 수정(미구현)\n");
    printf("4. 직원 정보 삭제(미구현)\n");
    printf("============================\n");
    printf("5. 부서 정보 보기\n");
    printf("6. 부서 정보 입력\n");
    printf("7. 부서 정보 수정(미구현)\n");
    printf("8. 부서 정보 삭제(미구현)\n");
    printf("============================\n");
    printf("9  직급 정보 보기\n");
    printf("0. 직급 정보 입력\n");
    printf("a. 직급 정보 수정(미구현)\n");
    printf("b. 직급 정보 삭제(미구현)\n");
    printf("============================\n");
    printf("x. 종료\n");
    printf("============================\n");
    printf("원하시는 메뉴를 선택하세요");
}


void ShowSubMenu()
{
    for (int i = 0; i < 50; i++) printf("=");

    printf("\n");
    printf("p. 이전 메뉴로 돌아가기\n");

    int n = 0;
    while (n = _getch())
    {
        if ('p' == n || 'P' == n)
            return;
    }
}


void PrintTitle(short mode)
{
    switch (mode)
    {
    case RW_EMPLOY:
        printf("사번\t");
        printf("이름\t\t");
        printf("부서코드\t");
        printf("직급코드\n");
        for (int i = 0; i < 50; i++)
            printf("=");

        printf("\n");
        break;

    case RW_BUSEO:
        printf("부서코드\t");
        printf("부서명\n");
        for (int i = 0; i < 30; i++)
            printf("=");
        printf("\n");
        break;

    case RW_JIKGUP:
        printf("직급코드\t");
        printf("직급명\n");
        for (int i = 0; i < 30; i++)
            printf("=");
        printf("\n");
        break;
    }
}

void PrintEmployRecord(void* pData, long empSize, BUSEO_CODE* pbu, long buSize, JIKGUP_CODE* pji, long jiSize)
{
    if (pData == NULL || empSize == 0)
        return;

    char tmp[20] = { 0 };
    EMPLOY* emp = (EMPLOY*)pData;

    printf("%d\t", emp->num);
    printf("%s\t\t", emp->name);
    GetBuseoName(emp->buseo, pbu, buSize, tmp, 20) ? printf("%s\t\t", tmp) : printf("%d\t\t", emp->buseo);
    memset(tmp, 0, 20);
    GetJikgupName(emp->jikgup, pji, jiSize, tmp, 20) ? printf("%s\n", tmp) : printf("%d\n", emp->jikgup);
    // printf("%d\n", emp->jikgup);
}

void PrintBuseoRecord(BUSEO_CODE* pbu, unsigned long buSize)
{
    if (pbu == NULL || buSize == 0)
        return;

    int nCount = buSize / sizeof(BUSEO_CODE);
    for (int i = 0; i < nCount; i++)
    {
        printf("%d\t", pbu[i].code);
        printf("%s\n", pbu[i].buseo_name);
    }
}

void PrintJikgupRecord(JIKGUP_CODE* pji, unsigned long jiSize)
{
    system("cls");
    PrintTitle(RW_JIKGUP);

    if (pji == NULL || jiSize == 0)
        return;

    int nCount = jiSize / sizeof(JIKGUP_CODE);
    for (int i = 0; i < nCount; i++)
    {
        printf("%d\t", pji[i].code);
        printf("%s\n", pji[i].jikgup_name);
    }
}


void PrintRecord(short mode, void* pData, long empSize, BUSEO_CODE* pbu, long buSize, JIKGUP_CODE* pji, long jiSize)
{
    system("cls");
    PrintTitle(mode);

    int nCount = 0;
    EMPLOY* pemp = (EMPLOY*)pData;

    switch (mode)
    {
    case RW_EMPLOY:
        if (pData == NULL || empSize == 0)
            return;

        nCount = empSize / sizeof(EMPLOY);
        for (int i = 0; i < nCount; i++)
            PrintEmployRecord(&pemp[i], empSize, pbu, buSize, pji, jiSize);
        break;


    case RW_BUSEO:
        if (pbu == NULL || buSize == 0)
            return;
        PrintBuseoRecord(pbu, (unsigned long)buSize);
        break;



    case RW_JIKGUP:
        if (pji == NULL || jiSize == 0)
            return;

        PrintJikgupRecord(pji, jiSize);
        break;
    
    }
    ShowSubMenu();
}

short InputRecord(EMPLOY* emp, EMPLOY *emps, unsigned long lSize)
{
    printf("직원 데이터베이스 입력 프로그램입니다\n\n");

    // fflush(stdin);
    rewind(stdin);

    int nRet = 0;
    short res = -1;
    do
    {
        printf("사번을 입력해주세요\n");
        nRet = scanf_s("%hd", &emp->num);
        if (!nRet) return 0;

        if ( emps && lSize )
            res = ExistCode(emp->num, RW_EMPLOY, (void*)emps, lSize);

        if (res == 1)
            printf("이미 존재하는 사원번호입니다. 다른 번호를 입력해주세요\n");

    } while (res == 1);

    if (!res) return 0;
    
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

short InputBuseo(BUSEO_CODE* code)
{
    printf("부서 기초 정보를 입력해주세요\n\n");

    fflush(stdin);
    rewind(stdin);

    int nRet = 0;
    printf("부서 코드를 입력해주세요\n");
    nRet = scanf_s("%hd", &code->code);
    if (!nRet) return 0;

    printf("부서 이름을 입력해주세요(한글 14자 제한)\n");
    nRet = scanf_s("%19s", code->buseo_name, (unsigned int)sizeof(code->buseo_name));
    if (!nRet) return 0;

    return 1;
}

short InputJikGup(JIKGUP_CODE* code)
{
    printf("직급 기초 정보를 입력해주세요\n\n");

    fflush(stdin);
    rewind(stdin);

    int nRet = 0;
    printf("직급 코드를 입력해주세요\n");
    nRet = scanf_s("%hd", &code->code);
    if (!nRet) return 0;

    printf("직급 이름을 입력해주세요(한글 14자 제한)\n");
    nRet = scanf_s("%19s", code->jikgup_name, (unsigned int)sizeof(code->jikgup_name));
    if (!nRet) return 0;

    return 1;
}


short GetBuseoName(short nCode, void* pData, long lSize, char* name, long bufSize) {
    if (name == NULL || lSize <= 0)
        return 0;

    BUSEO_CODE* pbu = (BUSEO_CODE*)pData;
    int nCount = lSize / sizeof(BUSEO_CODE);
    for (int i = 0; i < nCount; i++)
    {
        if (nCode == pbu[i].code)
        {
            strcpy_s(name, bufSize, pbu[i].buseo_name);
            return 1;
        }
    }

    return 0;
}

short GetJikgupName(short nCode, void* pData, long lSize, char* name, long bufSize)
{
    if (name == NULL || lSize <= 0)
        return 0;

    JIKGUP_CODE* pji = (JIKGUP_CODE*)pData;
    int nCount = lSize / sizeof(JIKGUP_CODE);
    for (int i = 0; i < nCount; i++)
    {
        if (nCode == pji[i].code)
        {
            strcpy_s(name, bufSize, pji[i].jikgup_name);
            return 1;
        }
    }


    return 0;
}
