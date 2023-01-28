// FileHandling.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <vcruntime_string.h>

#include "MyFileHandle.h"
#include <malloc.h>

//static int readCount = 0;
//static EMPLOY empArr[MAX_RECORDS] = {0};

int main()
{
    short nRes = 0;

    EMPLOY* pem = NULL;
    BUSEO_CODE* pbu = NULL;
    JIKGUP_CODE* pji = NULL;


    unsigned long lSize = 0;
    unsigned long buSize = 0;
    unsigned long jiSize = 0;



    nRes = GetFileSize(EMPLOY_FILE, &lSize);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        return 0;
    }

    
    pem = (EMPLOY*)malloc(lSize);
    if (pem == NULL)
        return 0;

    
    memset(pem, 0, lSize);
    nRes = ReadFromFile(pem, lSize, RW_EMPLOY, OnFileHandleEvent);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }
           

    // 부서
    
    nRes = GetFileSize(BUSEO_FILE, &buSize);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }
    
    pbu = (BUSEO_CODE*)malloc(buSize);
    if (pbu == NULL)
        goto ReleaseMem;
    
    
    memset(pbu, 0, buSize);
    nRes = ReadFromFile(pbu, buSize, RW_BUSEO, NULL);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }

    //PrintTitle(RW_BUSEO);
    //for (unsigned long p = 0; p < (lSize / sizeof(BUSEO_CODE)); p++)
    //{
    //    PrintRecord(&pbu[p], RW_BUSEO);
    //}

    // 직급
    
    nRes = GetFileSize(JIKGUP_FILE, &jiSize);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }

    pji = (JIKGUP_CODE*)malloc(jiSize);
    if (pji == NULL)
        goto ReleaseMem;


    memset(pji, 0, jiSize);
    nRes = ReadFromFile(pji, jiSize, RW_JIKGUP, NULL);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }

    //PrintTitle(RW_JIKGUP);
    //for (unsigned long p = 0; p < (lSize / sizeof(JIKGUP_CODE)); p++)
    //{
    //    PrintRecord(&pji[p], RW_JIKGUP);
    //}


    PrintTitle(RW_EMPLOY);
    for (unsigned long p = 0; p < (lSize / sizeof(EMPLOY)); p++)
    {
        // PrintRecord(&pem[p], RW_EMPLOY);
        PrintEmployRecord(&pem[p], lSize, pbu, buSize, pji, jiSize);
    }

    

ReleaseMem:
    
    if ( pem!=NULL )
    {
        free(pem);
        pem = NULL;
    }
    
    if (pbu != NULL)
    {
        free(pbu);
        pbu = NULL;
    }

    if (pji != NULL)
    {
        free(pji);
        pji = NULL;
    }
    

    // 고치고 다시 푸시

    //unsigned long lSize = 0;
    //nRes = GetFileSize(EMPLOY_FILE, &lSize);
    //if (nRes != SUCCESS_OPERATION)
    //{
    //    ErrorHandle(nRes);
    //    return 0;
    //}

    //EMPLOY* pem = (EMPLOY*)malloc(lSize);
    //if (pem)
    //{
    //    memset(pem, 0, lSize);
    //    nRes = ReadFromFile(pem, lSize, RW_EMPLOY, OnFileHandleEvent);
    //    if (nRes != SUCCESS_OPERATION)
    //    {
    //        ErrorHandle(nRes);
    //        return 0;
    //    }
    //}

    //for (unsigned long p = 0; p < (lSize/ sizeof(EMPLOY)); p++ )
    //{
    //    PrintRecord(&pem[p]);
    //}
    //
    //free(pem);
    //pem = NULL;
    

    // printf("sizeof(EMPLOY)= %zd\n", sizeof(EMPLOY));      

    /*JIKGUP_CODE jikgup;
    memset(&jikgup, 0, sizeof(JIKGUP_CODE));

    nRes = ReadFromFile(&jikgup, RW_JIKGUP, OnFileHandleEvent);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        return 0;
    }*/


    


    //nRes = InputJikGup(&jikgup);
    //if (!nRes)
    //    printf("직급 정보 입력 실패!\n");
    //
    //nRes = WriteToFile(&jikgup, RW_JIKGUP);
    //if (nRes != SUCCESS_OPERATION )
    //{
    //    ErrorHandle(nRes);
    //    return 0;
    //}
    
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
  
 /*   BUSEO_CODE code;
    memset(&code, 0, sizeof(BUSEO_CODE));
    nRes = ReadFromFile(&code, RW_BUSEO, OnFileHandleEvent);
    if (nRes != SUCCESS_OPERATION)
    {
        ErrorHandle(nRes);
        return 0;
    }*/
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
    
    // PrintRecord(&emp);

    return 0;
}


// void OnFileHandleEvent(void* p, unsigned int nCode)
void OnFileHandleEvent(void* p, unsigned long size, unsigned int nCode)
{
    switch (nCode)
    {
        case FILE_ACR_EMPLOY:
            // printf("Read Succeeded!\n");
            break;

        case FILE_ACR_BUSEO:
        {
            /*BUSEO_CODE* code = NULL;
            code = (BUSEO_CODE*)p;
            printf("부서코드 : %d\n", code->code);
            printf("부서명  : %s\n", code->buseo_name);
            break;*/
        }        

        case FILE_ACR_JIKGUP:
        {
            /*JIKGUP_CODE* code = NULL;
            code = (JIKGUP_CODE*)p;
            printf("직급코드 : %d\n", code->code);
            printf("직급명 : %s\n", code->jikgup_name);
            break;*/
        }        
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
