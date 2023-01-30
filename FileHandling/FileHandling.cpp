// FileHandling.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "MyFileHandle.h"


int main()
{
    short nRes = 0;

    EMPLOY* pem = NULL;
    BUSEO_CODE* pbu = NULL;
    JIKGUP_CODE* pji = NULL;

    unsigned long lSize = 0;
    unsigned long buSize = 0;
    unsigned long jiSize = 0;

    int n = 0;

    if (!ExistFile(EMPLOY_FILE))
    {
        EMPLOY emp;
        InputRecord(&emp);
        WriteToFile(&emp, sizeof(EMPLOY), RW_EMPLOY);
    }


    // 직원 정보 메모리에 로딩
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
           

    // 부서 정보 메모리에 로딩
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


    // 직급정보 메모리에 로딩
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

    //
    // 메뉴 핸들링
    while (TRUE)
    {
        ShowMenu();

        n = _getch();
        system("cls");

        switch (n)
        {
        case '1': // 직원 정보 출력
            PrintRecord(RW_EMPLOY, pem, lSize, pbu, buSize, pji, jiSize);
            break;

        case '2':   // 직원 정보 입력
        {
            EMPLOY emp;
            memset(&emp, 0, sizeof(EMPLOY));
            if (InputRecord(&emp))
            {   
                if (!AppendData((void**)&pem, &lSize, (void*)&emp, sizeof(EMPLOY)))
                {
                    printf("데이터 추가 실패!");
                    _getch();
                    break;
                }

                if ( !WriteToFile(pem, lSize, RW_EMPLOY) )
                {
                    printf("데이터 추가 실패!");
                    _getch();
                    break;
                }

                PrintRecord(RW_EMPLOY, pem, lSize, pbu, buSize, pji, jiSize);
            }
            break;
        }

        case '5':
            PrintRecord(RW_BUSEO, pem, lSize, pbu, buSize, pji, jiSize);
            break;

        case 'x':
        case 'X':
            goto ReleaseMem;

        default:
            break;
        }
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
        case FILE_ACR_BUSEO:
        case FILE_ACR_JIKGUP:    break;
    }
}