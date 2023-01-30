//
// 2023�� 1�� 30��, Coded by E.B Kim
//
// �ʰ��� �λ�������� �޴� �� ���� ���÷��� ���� �Լ���
//
// ���̼��� ����(������ ���̼���)



#include "showinfo.h"


void ShowMenu()
{
    system("cls");

    printf("1. ���� ���� ����\n");
    printf("2. ���� ���� �Է�\n");
    printf("3. ���� ���� ����(�̱���)\n");
    printf("4. ���� ���� ����(�̱���)\n");
    printf("============================\n");
    printf("5. �μ� ���� ����\n");
    printf("6. �μ� ���� �Է�\n");
    printf("7. �μ� ���� ����(�̱���)\n");
    printf("8. �μ� ���� ����(�̱���)\n");
    printf("============================\n");
    printf("9  ���� ���� ����\n");
    printf("0. ���� ���� �Է�\n");
    printf("a. ���� ���� ����(�̱���)\n");
    printf("b. ���� ���� ����(�̱���)\n");
    printf("============================\n");
    printf("x. ����\n");
    printf("============================\n");
    printf("���Ͻô� �޴��� �����ϼ���");
}


void ShowSubMenu()
{
    for (int i = 0; i < 50; i++) printf("=");

    printf("\n");
    printf("p. ���� �޴��� ���ư���\n");

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
    printf("���� �����ͺ��̽� �Է� ���α׷��Դϴ�\n\n");

    // fflush(stdin);
    rewind(stdin);

    int nRet = 0;
    short res = -1;
    do
    {
        printf("����� �Է����ּ���\n");
        nRet = scanf_s("%hd", &emp->num);
        if (!nRet) return 0;

        if ( emps && lSize )
            res = ExistCode(emp->num, RW_EMPLOY, (void*)emps, lSize);

        if (res == 1)
            printf("�̹� �����ϴ� �����ȣ�Դϴ�. �ٸ� ��ȣ�� �Է����ּ���\n");

    } while (res == 1);

    if (!res) return 0;
    
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

short InputBuseo(BUSEO_CODE* code)
{
    printf("�μ� ���� ������ �Է����ּ���\n\n");

    fflush(stdin);
    rewind(stdin);

    int nRet = 0;
    printf("�μ� �ڵ带 �Է����ּ���\n");
    nRet = scanf_s("%hd", &code->code);
    if (!nRet) return 0;

    printf("�μ� �̸��� �Է����ּ���(�ѱ� 14�� ����)\n");
    nRet = scanf_s("%19s", code->buseo_name, (unsigned int)sizeof(code->buseo_name));
    if (!nRet) return 0;

    return 1;
}

short InputJikGup(JIKGUP_CODE* code)
{
    printf("���� ���� ������ �Է����ּ���\n\n");

    fflush(stdin);
    rewind(stdin);

    int nRet = 0;
    printf("���� �ڵ带 �Է����ּ���\n");
    nRet = scanf_s("%hd", &code->code);
    if (!nRet) return 0;

    printf("���� �̸��� �Է����ּ���(�ѱ� 14�� ����)\n");
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
