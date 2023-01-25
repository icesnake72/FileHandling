#pragma once

typedef struct {
    short num;      // ���
    char name[30];  // �̸�
    short buseo;    // �μ�
    short jikgup;   // ����
} EMPLOY;

#define CANNOT_OPEN_FILE    0
#define CANNOT_WRITE        -1
#define CANNOT_READ         -2
#define SUCCESS_OPERATION   1


void PrintRecord(EMPLOY* emp);

short InputRecord(EMPLOY* emp);

short WriteToFile(EMPLOY* emp);

short ReadFromFile(EMPLOY* emp);

void ErrorHandle(short errCode);