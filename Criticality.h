/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2AP-CommonDataTypes"
 * 	found in "e2ap-v01.00.00.asn"
 * 	`asn1c -fcompound-names -fincludes-quoted -fno-include-deps -findirect-choice -gen-PER -D.`
 */

#ifndef	_Criticality_H_
#define	_Criticality_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Criticality {
	Criticality_reject	= 0,
	Criticality_ignore	= 1,
	Criticality_notify	= 2
} e_Criticality;

/* Criticality */
typedef long	 Criticality_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_Criticality_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_Criticality;
extern const asn_INTEGER_specifics_t asn_SPC_Criticality_specs_1;
asn_struct_free_f Criticality_free;
asn_struct_print_f Criticality_print;
asn_constr_check_f Criticality_constraint;
ber_type_decoder_f Criticality_decode_ber;
der_type_encoder_f Criticality_encode_der;
xer_type_decoder_f Criticality_decode_xer;
xer_type_encoder_f Criticality_encode_xer;
oer_type_decoder_f Criticality_decode_oer;
oer_type_encoder_f Criticality_encode_oer;
per_type_decoder_f Criticality_decode_uper;
per_type_encoder_f Criticality_encode_uper;
per_type_decoder_f Criticality_decode_aper;
per_type_encoder_f Criticality_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _Criticality_H_ */
#include "asn_internal.h"
