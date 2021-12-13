#include <stdio.h>
#include <stdlib.h>

#define FUNC_CALL() do{\
    printf("\033[34m[CALL][%s:%d] Called\033[m\n", __func__, __LINE__); \
    }while(0)
    
#define PRINT_ERROR(fmt...) do{\
    printf("\033[1;31m[ERROR][%s:%d] \033[m", __func__, __LINE__); \
    printf(fmt);\
    }while(0)


int test_E2AP_PDU_wrapper();
int test_RICcontrolRequest();

#define TEST 
static void __attribute__((unused)) test()
{
#ifdef TEST
    test_RICcontrolRequest();
    test_E2AP_PDU_wrapper();

    exit(1);
#endif
}
