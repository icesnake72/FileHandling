// FileHandling.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <vcruntime_string.h>

#include "MyFileHandle.h"



int main()
{
    short nRes = 0;
    EMPLOY emp;
    memset(&emp, 0, sizeof(EMPLOY));

    // printf("sizeof(EMPLOY)= %zd\n", sizeof(EMPLOY));      
    
    /*
    if (!InputRecord(&emp))
    {
        printf("데이터를 입력받을 수 없습니다.\n");
        return 0;
    }
    PrintRecord(&emp);

    nRes = WriteToFile(&emp);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        return 0;
    }
    
    
    PrintTitle();
    nRes = ReadFromFile(&emp, OnFileHandleEvent);
    if ( nRes!= SUCCESS_OPERATION )
    {
        ErrorHandle(nRes);
        return 0;
    }
    */    
    
    BUSEO_CODE code;
    memset(&code, 0, sizeof(BUSEO_CODE));
    nRes = ReadFromFile(&code, RW_BUSEO, OnFileHandleEvent);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        return 0;
    }
    /*    
    if (!InputBuseo(&code))
    {
        printf("데이터를 입력받을 수 없습니다.\n");
        return 0;
    }

    nRes = WriteToFile(&code, RW_BUSEO);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        return 0;
    }
    */
    
    PrintRecord(&emp);
    



    return 0;
}


void OnFileHandleEvent(void* p, unsigned int nCode)
{
    if ( nCode== FILE_ACR_EMPLOY)
        PrintRecord((EMPLOY*)p);

    else if (nCode == FILE_ACR_BUSEO)
    {
        BUSEO_CODE *code;
        code = (BUSEO_CODE*)p;
        printf("부서코드 : %d\n", code->code);
        printf("부서명  : %s\n", code->buseo_name);
    }
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
