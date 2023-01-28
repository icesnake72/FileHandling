#include <stdio.h>
#include <vcruntime_string.h>
#include <string.h>

#include "MyFileHandle.h"



void ErrorHandle(short errCode)
{
    switch (errCode)
    {
    case CANNOT_OPEN_FILE:
        printf("������ ���� ���߽��ϴ�.\n");
        break;

    case CANNOT_WRITE:
        printf("���Ͼ��� ����\n");
        break;
    }
}

void PrintTitle(short mode)
{
    switch (mode)
    {
    case RW_EMPLOY:
        printf("���\t");
        printf("�̸�\t\t");
        printf("�μ��ڵ�\t");
        printf("�����ڵ�\n");
        for (int i = 0; i < 50; i++)
            printf("=");

        printf("\n");
        break;

    case RW_BUSEO:
        printf("�μ��ڵ�\t");
        printf("�μ���\n");
        for (int i = 0; i < 30; i++)
            printf("=");
        printf("\n");
        break;

    case RW_JIKGUP:
        printf("�����ڵ�\t");
        printf("���޸�\n");
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
    printf("%d\n", emp->jikgup);
}

// void PrintRecord(EMPLOY* emp)
void PrintRecord(short mode, void* pData, long empSize, BUSEO_CODE *pbu, long buSize, JIKGUP_CODE *pji, long jiSize)
{
    /*EMPLOY* emp = NULL;
    BUSEO_CODE* pbu = NULL;
    JIKGUP_CODE* pji = NULL;*/
    
    switch (mode)
    {
    case RW_EMPLOY:
        PrintEmployRecord(pData, empSize, pbu, buSize, pji, jiSize);
        break;  
        

    case RW_BUSEO:
        {
            BUSEO_CODE* pbu = (BUSEO_CODE*)pData;
            printf("%d\t", pbu->code);
            printf("%s\n", pbu->buseo_name);
            break;
        }
        

    case RW_JIKGUP:
        {
            JIKGUP_CODE* pji = (JIKGUP_CODE*)pData;
            printf("%d\t", pji->code);
            printf("%s\n", pji->jikgup_name);
            break;
        }        
    }

    
}

short InputRecord(EMPLOY* emp)
{    
    printf("���� �����ͺ��̽� �Է� ���α׷��Դϴ�\n\n");

    int nRet = 0;
    printf("����� �Է����ּ���\n");
    nRet = scanf_s("%hd", &emp->num);
    if (!nRet) return 0;
    
    printf("���� �̸��� �Է����ּ���(�ѱ� 14�� ����)\n");
    nRet = scanf_s("%29s", emp->name, (unsigned int)sizeof(emp->name));
    if (!nRet) return 0;
        
    printf("�μ� �ڵ带 �Է����ּ���\n");
    nRet = scanf_s("%hd", &emp->buseo);
    if (!nRet) return 0;

    printf("���� �ڵ带 �Է����ּ���\n");
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

    // (nRet) ? printf("���Ͼ��� ����(%zd block(s))\n", nRet) : printf("���Ͼ��� ����\n");
    fclose(fp);
    fp = NULL;

    return SUCCESS_OPERATION;
}



// short ReadFromFile(EMPLOY* emp, void (*ptrFileHandler)(void* p, unsigned int nCode), unsigned short toReadCount)
short ReadFromFile(void* pData, unsigned long dataSize, int nCode, void (*ptrFileHandler)(void* p, unsigned long size, unsigned int nCode), unsigned short toReadCount)
{
    unsigned short buffSize = 0;
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
    printf("�μ� ���� ������ �Է����ּ���\n\n");

    int nRet = 0;
    printf("�μ� �ڵ带 �Է����ּ���\n");
    nRet = scanf_s("%hd", &code->code);
    if (!nRet) return 0;

    printf("�μ� �̸��� �Է����ּ���(�ѱ� 14�� ����)\n");
    nRet = scanf_s("%19s", code->buseo_name, (unsigned int)sizeof(code->buseo_name));
    if (!nRet) return 0;
        
    return 1;
}

short InputJikGup(JIKGUP_CODE *code)
{
    printf("���� ���� ������ �Է����ּ���\n\n");

    int nRet = 0;
    printf("���� �ڵ带 �Է����ּ���\n");
    nRet = scanf_s("%hd", &code->code);
    if (!nRet) return 0;

    printf("���� �̸��� �Է����ּ���(�ѱ� 14�� ����)\n");
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
    return 0;
}

