/**
 *  测试 E2AP_PDU
 *  
 *
 *  作者：荣涛
 *  创建时间：2021年8月31日11:19:30
 *  
 *  修改日志
 *  2021年8月31日    创建
 */
#include "my-test/my_test.h"


//#define TEST_E2AP_PDU

int test_E2AP_PDU_wrapper()
{
#ifdef TEST_E2AP_PDU
    FUNC_CALL();

    E2AP_PDU_t E2AP_PDU;

    E2AP_PDU.present = E2AP_PDU_PR_initiatingMessage;
//    E2AP_PDU.choice.initiatingMessage->

    //TODO

#endif

    return 0;
}

