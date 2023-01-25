#include <stdio.h>

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

void PrintRecord(EMPLOY* emp)
{
    printf("��� : %d\n", emp->num);
    printf("�̸� : %s\n", emp->name);
    printf("�μ��ڵ� : %d\n", emp->buseo);
    printf("�����ڵ� : %d\n", emp->jikgup);
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

    // (nRet) ? printf("���Ͼ��� ����(%zd block(s))\n", nRet) : printf("���Ͼ��� ����\n");
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