#pragma once

typedef struct {
    short num;      // 사번
    char name[30];  // 이름
    short buseo;    // 부서
    short jikgup;   // 직급
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