

#include "MyFileHandle.h"


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
    printf("a. 직급 정보 입력\n");
    printf("b. 직급 정보 수정(미구현)\n");
    printf("c. 직급 정보 삭제(미구현)\n");
    printf("============================\n");
    printf("x. 종료\n");    
    printf("============================\n");
    printf("원하시는 메뉴를 선택하세요");
}


void ShowSubMenu()
{   
    for(int i=0; i<50; i++) printf("=");
    
    printf("\n");
    printf("p. 이전 메뉴로 돌아가기\n");
        
    int n = 0;
    while ( n = _getch() )
    {
        if ('p' == n || 'P' == n)
            return;        
    }
}


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

void PrintEmployRecord(void *pData, long empSize, BUSEO_CODE* pbu, long buSize, JIKGUP_CODE* pji, long jiSize)
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


void PrintRecord(short mode, void* pData, long empSize, BUSEO_CODE *pbu, long buSize, JIKGUP_CODE *pji, long jiSize)
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
        for(int i=0; i<nCount; i++)
            PrintEmployRecord(&pemp[i], empSize, pbu, buSize, pji, jiSize);
        break;  
        

    case RW_BUSEO:        
        PrintBuseoRecord(pbu, (unsigned long)buSize);        
        break;
        
        

    case RW_JIKGUP:
        {
            JIKGUP_CODE* pji = (JIKGUP_CODE*)pData;
            printf("%d\t", pji->code);
            printf("%s\n", pji->jikgup_name);
            break;
        }        
    }
    ShowSubMenu();
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

int SetFileNameAndDataSize(int nCode, char* szFileName, unsigned short fileNameLen, unsigned long *lSize)
{
    switch (nCode)
    {
    case RW_EMPLOY:
        strcpy_s(szFileName, FILE_NAME_LEN, EMPLOY_FILE);
        *lSize = sizeof(EMPLOY);
        break;

    case RW_BUSEO:
        strcpy_s(szFileName, FILE_NAME_LEN, BUSEO_FILE);        
        *lSize = sizeof(BUSEO_CODE);
        break;

    case RW_JIKGUP:
        strcpy_s(szFileName, FILE_NAME_LEN, JIKGUP_FILE);        
        *lSize = sizeof(JIKGUP_CODE);
        break;

    default:        
        return INVALID_CODE;
    }

    return SUCCESS_OPERATION;
}


// short WriteToFile(EMPLOY* emp)
short WriteToFile(void* pData, unsigned long lDataSize, int nCode)
{
    if (pData == NULL || lDataSize == 0)
        return INVALID_PARAM;

    unsigned long bufSize = 0;
    char szFileName[FILE_NAME_LEN];
    memset(szFileName, 0, FILE_NAME_LEN);
    if (SetFileNameAndDataSize(nCode, szFileName, FILE_NAME_LEN, &bufSize)== INVALID_CODE)
        return INVALID_CODE;
    
    FILE* fp = NULL;
    fopen_s(&fp, szFileName, "wb");
    if (fp == NULL)
    {        
        return CANNOT_OPEN_FILE;
    }

    // printf("sizeof(EMPLOY)=%zd\n", sizeof(EMPLOY));
    // PrintRecord(emp);

    size_t nRet = 0;
    nRet = fwrite(pData, lDataSize, 1, fp);
    if (!nRet)
    {
        fclose(fp);
        fp = NULL;
        return CANNOT_WRITE;
    }

    // (nRet) ? printf("파일쓰기 성공(%zd block(s))\n", nRet) : printf("파일쓰기 실패\n");
    fclose(fp);
    fp = NULL;

    return SUCCESS_OPERATION;
}



// short ReadFromFile(EMPLOY* emp, void (*ptrFileHandler)(void* p, unsigned int nCode), unsigned short toReadCount)
short ReadFromFile(void* pData, unsigned long dataSize, int nCode, void (*ptrFileHandler)(void* p, unsigned long size, unsigned int nCode), unsigned short toReadCount)
{
    unsigned long buffSize = 0;
    char szFileName[FILE_NAME_LEN];
    memset(szFileName, 0, FILE_NAME_LEN);
    if (SetFileNameAndDataSize(nCode, szFileName, FILE_NAME_LEN, &buffSize) == INVALID_CODE)
        return INVALID_CODE;

    unsigned int readDataCode = 0;
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

    // char* p = (char *)pData;
    size_t readedCount = dataSize/buffSize;
    // do {
        size_t nRet = fread_s(pData, dataSize, buffSize, readedCount, fp);
        if (!nRet)
        {
            fclose(fp);
            fp = NULL;
            return CANNOT_READ;
        }

        if ( ptrFileHandler )
            ptrFileHandler(pData, dataSize, readDataCode);

//         readedCount++;
        // p += buffSize;

    // } while (!feof(fp) && readedCount < toReadCount);
    fclose(fp);
    fp = NULL;

    return SUCCESS_OPERATION;
}

short GetFileSize(const char* filename, unsigned long *size)
{
    FILE* fp = NULL;
    fopen_s(&fp, filename, "rb");
    if (fp == NULL)
    {
        return CANNOT_OPEN_FILE;
    }

    if (fseek(fp, 0, SEEK_END) != 0)
    { 
        fclose(fp);
        fp = NULL;
        return CANNOT_SEEK;
    }
    
    *size = ftell(fp);
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


short GetBuseoName(short nCode, void *pData, long lSize, char* name, long bufSize) {
    if (name == NULL || lSize<=0 )
        return 0;

    BUSEO_CODE* pbu = (BUSEO_CODE *)pData;
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


short AppendData(void **ppData, unsigned long *lSizeData, void *pAppend, unsigned long lAppendSize)
{
    if (ppData == NULL || *lSizeData==0 || pAppend==NULL || lAppendSize==0 )
        return 0;

    unsigned long lNewSize = *lSizeData + lAppendSize;
    char* pNewData = (char *)malloc(lNewSize);
    if (pNewData == NULL)
        return 0;

    memcpy(pNewData, *ppData, *lSizeData);
    memcpy(pNewData + *lSizeData, pAppend, lAppendSize);

    free(*ppData);
    *ppData = NULL;

    *ppData = pNewData;
    *lSizeData = lNewSize;

    return 1;
}


short ExistFile(const char* filename)
{
    int ret = 0;
    FILE* fp = NULL;
    fopen_s(&fp, filename, "r");
    if (fp == NULL)
        return 0;

    
    fclose(fp);
    fp = NULL;
    return 1;    
}


