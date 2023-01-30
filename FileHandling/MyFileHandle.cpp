//
// 2023년 1월 30일, Coded by E.B Kim
//
// 간략 RDB 구현
// 동적 메모리 할당
// 구조체와 포인터
// 이중 포인터 사용
//
// 라이선스 없음(무제한 라이선스)



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

short ExistCode(short code, short nMode, void* pData, unsigned long lSizeData)
{
    // return -1 ===> 없음
    // return 1 ===> 있음
    // return 0 ===> 프로세스 에러

    if (pData == NULL || lSizeData == 0)
        return 0;
    
    int nCount = 0;
    switch (nMode)
    {
    case RW_EMPLOY:
    {
        EMPLOY* pem = (EMPLOY*)pData;
        nCount = lSizeData / sizeof(EMPLOY);
        for (int i = 0; i < nCount; i++)
        {
            if (code == pem[i].num)
                return 1;
        }
        break;
    }
    case RW_BUSEO:
    {
        BUSEO_CODE *pbu = (BUSEO_CODE*)pData;
        nCount = lSizeData / sizeof(BUSEO_CODE);
        for (int i = 0; i < nCount; i++)
        {
            if (code == pbu[i].code)
                return 1;
        }
        break;
    }
    case RW_JIKGUP:
    {
        JIKGUP_CODE *pji = (JIKGUP_CODE*)pData;;
        nCount = lSizeData / sizeof(JIKGUP_CODE);
        for (int i = 0; i < nCount; i++)
        {
            if (code == pji[i].code)
                return 1;
        }
        break;
    }
    
    }

    return -1;
}


