#pragma once
#include"scaning.h"

#ifndef NULL
#define NULL 0
#endif

#define VT_SIZE_	13
#define VT_begin	1
#define VT_end		2
#define VT_smcl		3
#define VT_id		4
#define VT_num		5
#define VT_lks		6
#define VT_rks		7
#define VT_op_mul	8
#define VT_op_div	9
#define VT_op_plu	10
#define VT_op_min	11
#define VT_is		12

#define VN_SIZE_	12
#define VN_MSP		1
#define VN_STP		2
#define VN_SP		3
#define VN_SPH		4
#define VN_ISP		5
#define VN_VP		6
#define VN_CP		7
#define VN_IP		8
#define VN_CPH		9
#define VN_DP		10
#define VN_IPH		11

void ll1_g_init();

int LL1_get_STRING_type(_TOKEN_TYPE_ token);
int LL1_get_STACK_type();