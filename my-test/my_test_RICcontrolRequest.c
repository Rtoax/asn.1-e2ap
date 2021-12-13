/**
 *  测试 RICcontrolRequest_t
 *  
 *
 *  作者：荣涛
 *  创建时间：2021年8月30日
 *  
 *  修改日志
 *  2021年8月30日 创建 xer 编解码
 *  2021年8月31日    尝试添加 ber 编解码, 
 *  2021年9月1日 aper 编解码 完成
 *  2021年9月2日 ber、der编解码
 */

#include <stdio.h>	/* for stdout */
#include <errno.h>	/* for errno */
#include <stdlib.h>	/* for malloc() */
#include <assert.h>	/* for run-time control */
#include "../RICcontrolRequest.h"	/* Include MyTypes definition */
#include "../ProtocolIE-Field.h"

#include "my-test/my_test.h"

#define XER_RICcontrolRequest "RICcontrolRequest.xer"
#define APER_RICcontrolRequest "RICcontrolRequest.aper"
#define OER_RICcontrolRequest "RICcontrolRequest.oer"
#define DER_RICcontrolRequest "RICcontrolRequest.ber"

#define NEW_XER_RICcontrolRequest "RICcontrolRequest-New.xer"
#define NEW_APER_RICcontrolRequest "RICcontrolRequest-New.aper"
#define NEW_OER_RICcontrolRequest "RICcontrolRequest-New.oer"
#define NEW_DER_RICcontrolRequest "RICcontrolRequest-New.ber"


static RICcontrolRequest_IEs_t *alloc_RICcontrolRequest_IEs(ProtocolIE_ID_t	 id, 
    RICcontrolRequest_IEs__value_PR choice, void *value)
{
    RICcontrolRequest_IEs_t *v = calloc(1, sizeof(RICcontrolRequest_IEs_t));
    assert(v && "NULL pointer");

    /**
     *  我不懂协议，这块不知道应该怎么填写（荣涛 2021年8月31日）
     */
    v->id = id;
    v->criticality = Criticality_reject;
    v->value.present = choice;
            
    switch(choice) {
    default:
    case RICcontrolRequest_IEs__value_PR_NOTHING:
        {
        printf("Nothing to do.\n");
        break;
        }
    case RICcontrolRequest_IEs__value_PR_RICrequestID:
        {
        RICrequestID_t *RICrequestID = (RICrequestID_t*)value;
        v->value.choice.RICrequestID.ricInstanceID = RICrequestID->ricInstanceID;
        v->value.choice.RICrequestID.ricRequestorID = RICrequestID->ricRequestorID;
        break;
        }
    case RICcontrolRequest_IEs__value_PR_RANfunctionID:
        {
        RANfunctionID_t *RANfunctionID = (RANfunctionID_t*)value;
        v->value.choice.RANfunctionID = *RANfunctionID;
        break;
        }
    case RICcontrolRequest_IEs__value_PR_RICcallProcessID:
        {
        RICcallProcessID_t *RICcallProcessID = (RICcallProcessID_t*)value;
        OCTET_STRING_fromBuf(&v->value.choice.RICcallProcessID, (char*)RICcallProcessID->buf, RICcallProcessID->size);
        break;
        }
    case RICcontrolRequest_IEs__value_PR_RICcontrolHeader:
        {
        RICcontrolHeader_t *RICcontrolHeader = (RICcontrolHeader_t*)value;
        OCTET_STRING_fromBuf(&v->value.choice.RICcontrolHeader, (char*)RICcontrolHeader->buf, RICcontrolHeader->size);
        break;
        }
    case RICcontrolRequest_IEs__value_PR_RICcontrolMessage:
        {
        RICcontrolMessage_t *RICcontrolMessage = (RICcontrolMessage_t*)value;
        OCTET_STRING_fromBuf(&v->value.choice.RICcontrolMessage, (char*)RICcontrolMessage->buf, RICcontrolMessage->size);
        break;
        }
    case RICcontrolRequest_IEs__value_PR_RICcontrolAckRequest:
        {
        RICcontrolAckRequest_t *RICcontrolAckRequest = (RICcontrolAckRequest_t*)value;
        v->value.choice.RICcontrolAckRequest = *RICcontrolAckRequest;
        break;
        }
    }

    return v;
}

static void fprintf_RICcontrolRequest(FILE* fp, RICcontrolRequest_t *RICcontrolRequest)
{
    xer_fprint(fp, &asn_DEF_RICcontrolRequest, RICcontrolRequest);

    fprintf(fp, "\n");
}

static void printf_RICcontrolRequest(RICcontrolRequest_t *RICcontrolRequest)
{
    fprintf_RICcontrolRequest(stdout, RICcontrolRequest);
}


static void save_RICcontrolRequest_xer(const char *filename, RICcontrolRequest_t *RICcontrolRequest)
{
    FILE *fp = fopen(filename, "w");

    fprintf_RICcontrolRequest(fp, RICcontrolRequest);

    fclose(fp);
}

static size_t encode_RICcontrolRequest_aper(RICcontrolRequest_t* pdu, void* buffer, size_t buf_size)
{
    asn_enc_rval_t encode_result;
    encode_result = aper_encode_to_buffer(&asn_DEF_RICcontrolRequest , NULL, pdu, buffer, buf_size);
//    ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest , pdu);
    if(encode_result.encoded == -1) {
        fprintf(stderr, "Cannot encode %s: %s\n", encode_result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return encode_result.encoded;
    }
}

static size_t encode_RICcontrolRequest_oer(RICcontrolRequest_t* pdu, void* buffer, size_t buf_size)
{
    asn_enc_rval_t encode_result;
    encode_result = oer_encode_to_buffer(&asn_DEF_RICcontrolRequest , NULL, pdu, buffer, buf_size);
//    ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest , pdu);
    if(encode_result.encoded == -1) {
        fprintf(stderr, "Cannot encode %s: %s\n", encode_result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return encode_result.encoded;
    }
}

static size_t encode_RICcontrolRequest_der(RICcontrolRequest_t* pdu, void* buffer, size_t buf_size)
{
    asn_enc_rval_t encode_result;
    encode_result = der_encode_to_buffer(&asn_DEF_RICcontrolRequest , pdu, buffer, buf_size);
//    ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest , pdu);
    if(encode_result.encoded == -1) {
        fprintf(stderr, "Cannot encode %s: %s\n", encode_result.failed_type->name, strerror(errno));
        return -1;
    } else {
        return encode_result.encoded;
    }
}


static void save_RICcontrolRequest_aper(const char *filename, RICcontrolRequest_t *RICcontrolRequest)
{
    char buffer[2048] = {0};
    size_t size = encode_RICcontrolRequest_aper(RICcontrolRequest, buffer, 2048);

    FILE *fp = fopen(filename, "w");
    fwrite(buffer, 1, size, fp);
    fclose(fp);
}

static void save_RICcontrolRequest_oer(const char *filename, RICcontrolRequest_t *RICcontrolRequest)
{
    char buffer[2048] = {0};
    size_t size = encode_RICcontrolRequest_oer(RICcontrolRequest, buffer, 2048);

    FILE *fp = fopen(filename, "w");
    fwrite(buffer, 1, size, fp);
    fclose(fp);
}

static void save_RICcontrolRequest_der(const char *filename, RICcontrolRequest_t *RICcontrolRequest)
{
    char buffer[2048] = {0};
    size_t size = encode_RICcontrolRequest_der(RICcontrolRequest, buffer, 2048);

    FILE *fp = fopen(filename, "w");
    fwrite(buffer, 1, size, fp);
    fclose(fp);
}


/**
 *  生成 RICcontrolRequest 结构体
 */
static int gen_RICcontrolRequest()
{
    RICcontrolRequest_t *RICcontrolRequest;

    RICcontrolRequest = calloc(1, sizeof(RICcontrolRequest_t));
	assert(RICcontrolRequest);	/* Assume infinite memory */

    /**
     *  
     */
    RICrequestID_t RICrequestID = {
        RICrequestID.ricInstanceID = 12,
        RICrequestID.ricRequestorID = 13,
    };
    RICcontrolRequest_IEs_t *RICcontrolRequest_IE = 
        alloc_RICcontrolRequest_IEs(ProtocolIE_ID_id_RICrequestID, 
            RICcontrolRequest_IEs__value_PR_RICrequestID, &RICrequestID);
    ASN_SEQUENCE_ADD(&RICcontrolRequest->protocolIEs.list, RICcontrolRequest_IE);

    /**
     *  
     */
    RANfunctionID_t RANfunctionID = 14;
    RICcontrolRequest_IEs_t *RICcontrolRequest_IE2 = 
        alloc_RICcontrolRequest_IEs(ProtocolIE_ID_id_RANfunctionID, 
            RICcontrolRequest_IEs__value_PR_RANfunctionID, &RANfunctionID);
    ASN_SEQUENCE_ADD(&RICcontrolRequest->protocolIEs.list, RICcontrolRequest_IE2);

    /**
     *  
     */
    RICcallProcessID_t RICcallProcessID;
    RICcallProcessID.buf = malloc(1);
    OCTET_STRING_fromBuf(&RICcallProcessID, "RICcallProcessID", strlen("RICcallProcessID"));
    
    RICcontrolRequest_IEs_t *RICcontrolRequest_IE3 = 
        alloc_RICcontrolRequest_IEs(ProtocolIE_ID_id_RICcallProcessID, 
            RICcontrolRequest_IEs__value_PR_RICcallProcessID, &RICcallProcessID);
    ASN_SEQUENCE_ADD(&RICcontrolRequest->protocolIEs.list, RICcontrolRequest_IE3);


    
    /**
     *  
     */
    RICcontrolHeader_t RICcontrolHeader;
    RICcontrolHeader.buf = malloc(1);
    OCTET_STRING_fromBuf(&RICcontrolHeader, "RICcontrolHeader", strlen("RICcontrolHeader"));
    
    RICcontrolRequest_IEs_t *RICcontrolRequest_IE4 = 
        alloc_RICcontrolRequest_IEs(ProtocolIE_ID_id_RICcontrolHeader, 
            RICcontrolRequest_IEs__value_PR_RICcontrolHeader, &RICcontrolHeader);
    ASN_SEQUENCE_ADD(&RICcontrolRequest->protocolIEs.list, RICcontrolRequest_IE4);


    /**
     *  
     */
    RICcontrolMessage_t RICcontrolMessage;
    RICcontrolMessage.buf = malloc(1);
    OCTET_STRING_fromBuf(&RICcontrolMessage, "RICcontrolMessage", strlen("RICcontrolMessage"));
    
    RICcontrolRequest_IEs_t *RICcontrolRequest_IE5 = 
        alloc_RICcontrolRequest_IEs(ProtocolIE_ID_id_RICcontrolMessage, 
            RICcontrolRequest_IEs__value_PR_RICcontrolMessage, &RICcontrolMessage);
    ASN_SEQUENCE_ADD(&RICcontrolRequest->protocolIEs.list, RICcontrolRequest_IE5);

    
    /**
     *  
     */
    RICcontrolAckRequest_t RICcontrolAckRequest = RICcontrolAckRequest_nAck;
    RICcontrolRequest_IEs_t *RICcontrolRequest_IE6 = 
        alloc_RICcontrolRequest_IEs(ProtocolIE_ID_id_RICcontrolAckRequest,
            RICcontrolRequest_IEs__value_PR_RICcontrolAckRequest, &RICcontrolAckRequest);
    ASN_SEQUENCE_ADD(&RICcontrolRequest->protocolIEs.list, RICcontrolRequest_IE6);

    /**
     *  输出到屏幕
     */
    printf("################ Original Struct ##################\n");
    printf_RICcontrolRequest(RICcontrolRequest);
    printf("##################################\n");

    /**
     *  将其保存为 多种 文件格式
     */
    save_RICcontrolRequest_xer(XER_RICcontrolRequest, RICcontrolRequest);
    save_RICcontrolRequest_aper(APER_RICcontrolRequest, RICcontrolRequest);
    save_RICcontrolRequest_oer(OER_RICcontrolRequest, RICcontrolRequest);
    save_RICcontrolRequest_der(DER_RICcontrolRequest, RICcontrolRequest);

    return 0;
    
}

static int decode_RICcontrolRequest_xer()
{
    FUNC_CALL();
    
    RICcontrolRequest_t *RICcontrolRequest = NULL;
	char buf[2048] = {0};
    int size;
	asn_dec_rval_t rval;
    
	FILE *fp = fopen(XER_RICcontrolRequest, "r");

    
	size = fread(buf, 1, sizeof buf, fp);
	if(size == 0 || size == sizeof buf) {
		PRINT_ERROR("%s: Too large input\n", XER_RICcontrolRequest);
		exit(1);
	}
    fclose(fp);

	rval = xer_decode(NULL, &asn_DEF_RICcontrolRequest, (void**)&RICcontrolRequest, buf, size);
    if(rval.code != RC_OK) {
        ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest, RICcontrolRequest);
        return -1;
    }
    
//    printf("################ Decode XER file ##################\n");
//    printf_RICcontrolRequest(RICcontrolRequest);
//    printf("##################################\n");

    
    save_RICcontrolRequest_xer(NEW_XER_RICcontrolRequest, RICcontrolRequest);
    
    ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest, RICcontrolRequest);
    return 0;
}

static int decode_RICcontrolRequest_aper()
{
    FUNC_CALL();
    
    RICcontrolRequest_t *RICcontrolRequest = NULL;
	char buf[2048] = {0};
    int size;
    
	FILE *fp = fopen(APER_RICcontrolRequest, "r");
    
	size = fread(buf, 1, sizeof buf, fp);
	if(size == 0 || size == sizeof buf) {
		fprintf(stderr, "%s: Too large input\n", APER_RICcontrolRequest);
		exit(1);
	}
    fclose(fp);

    asn_dec_rval_t decode_result;
    decode_result = aper_decode_complete(NULL, &asn_DEF_RICcontrolRequest, (void **)&RICcontrolRequest, buf, size);
    if(decode_result.code != RC_OK) {
        ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest, RICcontrolRequest);
        return -1;
    }
    
//    printf("################# Decode APER file #################\n");
//    printf_RICcontrolRequest(RICcontrolRequest);
//    printf("##################################\n");
    
    save_RICcontrolRequest_aper(NEW_APER_RICcontrolRequest, RICcontrolRequest);
    
    ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest, RICcontrolRequest);
    return 0;
}


static int decode_RICcontrolRequest_oer()
{
    FUNC_CALL();
    
    RICcontrolRequest_t *RICcontrolRequest = NULL;
	char buf[2048] = {0};
    int size;
    
	FILE *fp = fopen(OER_RICcontrolRequest, "r");
    
	size = fread(buf, 1, sizeof buf, fp);
	if(size == 0 || size == sizeof buf) {
		PRINT_ERROR("%s: Too large input\n", OER_RICcontrolRequest);
		exit(1);
	}
    fclose(fp);

    asn_dec_rval_t decode_result;
//    oer_decode_primitive(NULL, &asn_DEF_RICcontrolRequest, (void **)&RICcontrolRequest, buf, size);
    decode_result = oer_decode(NULL, &asn_DEF_RICcontrolRequest, (void **)&RICcontrolRequest, buf, size);
    if(decode_result.code != RC_OK) {
        PRINT_ERROR("error. size = %d, ret = %d\n", size, decode_result.code);
        ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest, RICcontrolRequest);
        return -1;
    }
    
//    printf("################# Decode OER file #################\n");
//    printf_RICcontrolRequest(RICcontrolRequest);
//    printf("##################################\n");
    
    save_RICcontrolRequest_oer(NEW_OER_RICcontrolRequest, RICcontrolRequest);
    
    ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest, RICcontrolRequest);
    return 0;
}


static int decode_RICcontrolRequest_der()
{
    FUNC_CALL();
    
    RICcontrolRequest_t *RICcontrolRequest = NULL;
	char buf[2048] = {0};
    int size;
    
	FILE *fp = fopen(DER_RICcontrolRequest, "r");
    
	size = fread(buf, 1, sizeof buf, fp);
	if(size == 0 || size == sizeof buf) {
		fprintf(stderr, "%s: Too large input\n", DER_RICcontrolRequest);
		exit(1);
	}
    fclose(fp);

    asn_dec_rval_t decode_result;
    decode_result = ber_decode(NULL, &asn_DEF_RICcontrolRequest, (void **)&RICcontrolRequest, buf, size);
    if(decode_result.code != RC_OK) {
        printf("error. size = %d, ret = %d\n", size, decode_result.code);
        ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest, RICcontrolRequest);
        return -1;
    }
    
    save_RICcontrolRequest_der(NEW_DER_RICcontrolRequest, RICcontrolRequest);
    
    ASN_STRUCT_FREE(asn_DEF_RICcontrolRequest, RICcontrolRequest);
    return 0;
}


static void load_RICcontrolRequest()
{
    decode_RICcontrolRequest_xer();
    decode_RICcontrolRequest_aper();
    decode_RICcontrolRequest_oer();
    decode_RICcontrolRequest_der();
}



/**
 *  RICcontrolRequest 测试例代码
 *
 *  作者 荣涛
 *  创建 2021年8月29日
 *
 */
#define TEST_RICcontrolRequest 
int test_RICcontrolRequest()
{

#ifdef TEST_RICcontrolRequest

    FUNC_CALL();
    
    gen_RICcontrolRequest();

    load_RICcontrolRequest();
    
#endif

    return 0;
}
