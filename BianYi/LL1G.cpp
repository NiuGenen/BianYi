#include"LL1G.h"
#include"stack.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int _1_MSP[4] = { VT_end,-VN_STP,VT_begin,0 };
int _2_STP[4] = { -VN_SPH,VT_smcl ,-VN_SP,0 };
int _3_SPH1[1] = { 0 };
int _4_SPH2[2] = { -VN_STP,0 };
int _5_SP[2] = { -VN_ISP,0 };
int _6_ISP[4] = { -VN_CP ,VT_is ,-VN_VP,0 };
int _7_VP[2] = { VT_id,0 };
int _8_CP[3] = { -VN_CPH ,-VN_IP,0 };
int _9_IP[3] = { -VN_IPH ,-VN_DP,0 };
int _10_DP1[2] = { -VN_VP,0 };
int _11_DP2[2] = { VT_num,0 };
int _12_DP3[4] = { VT_rks,-VN_CP,VT_lks,0 };
int _13_IPH1[1] = { 0 };
int _14_IPH2[3] = { -VN_IP,VT_op_mul,0 };
int _15_IPH3[3] = { -VN_IP,VT_op_div,0 };
int _16_CPH1[1] = { 0 };
int _17_CPH2[3] = { -VN_CP,VT_op_plu,0 };
int _18_CPH3[3] = { -VN_CP,VT_op_min,0 };

int ***matrix_LL1 = NULL;
_STACK_ stack_LL1;

void ll1_g_init() {
	_stack_init(&stack_LL1, STACK_CONTAIN);
	stack_LL1.push(&stack_LL1, -VN_MSP);

	matrix_LL1 = (int ***)malloc(sizeof(int**)*VN_SIZE_);
	for (int i = 0; i < VN_SIZE_; ++i) {
		matrix_LL1[i] = (int **)malloc(sizeof(int*)*VT_SIZE_);
		memset(matrix_LL1[i], NULL, sizeof(int*)*VT_SIZE_);
	}

	matrix_LL1[VN_MSP][VT_begin] = _1_MSP;
	matrix_LL1[VN_STP][VT_id] = _2_STP;
	matrix_LL1[VN_SP][VT_id] = _5_SP;
	matrix_LL1[VN_SPH][VT_end] = _3_SPH1;
	matrix_LL1[VN_SPH][VT_id] = _4_SPH2;
	matrix_LL1[VN_ISP][VT_id] = _6_ISP;
	matrix_LL1[VN_VP][VT_id] = _7_VP;
	matrix_LL1[VN_CP][VT_id] = _8_CP;
	matrix_LL1[VN_CP][VT_num] = _8_CP;
	matrix_LL1[VN_CP][VT_lks] = _8_CP;
	matrix_LL1[VN_IP][VT_id] = _9_IP;
	matrix_LL1[VN_IP][VT_num] = _9_IP;
	matrix_LL1[VN_IP][VT_lks] = _9_IP;
	matrix_LL1[VN_CPH][VT_end] = _16_CPH1;
	matrix_LL1[VN_CPH][VT_smcl] = _16_CPH1;
	matrix_LL1[VN_CPH][VT_rks] = _16_CPH1;
	matrix_LL1[VN_CPH][VT_op_plu] = _17_CPH2;
	matrix_LL1[VN_CPH][VT_op_min] = _18_CPH3;
	matrix_LL1[VN_DP][VT_id] = _10_DP1;
	matrix_LL1[VN_DP][VT_num] = _11_DP2;
	matrix_LL1[VN_DP][VT_lks] = _12_DP3;
	matrix_LL1[VN_IPH][VT_id] = _13_IPH1;
	matrix_LL1[VN_IPH][VT_num] = _13_IPH1;
	matrix_LL1[VN_IPH][VT_rks] = _13_IPH1;
	//matrix_LL1[VN_IPH][VT_end] = _13_IPH1;
	matrix_LL1[VN_IPH][VT_smcl] = _13_IPH1;
	matrix_LL1[VN_IPH][VT_op_mul] = _14_IPH2;
	matrix_LL1[VN_IPH][VT_op_div] = _15_IPH3;
	matrix_LL1[VN_IPH][VT_op_plu] = _13_IPH1;
	matrix_LL1[VN_IPH][VT_op_min] = _13_IPH1;
}

int LL1_get_STRING_type(_TOKEN_TYPE_ token) {
	switch (token.type)
	{
	case TOKEN_CMP:
	case TOKEN_UND:
	case TOKEN_END:
		return 0;
		break;
	case TOKEN_ID:
		return VT_id;
		break;
	case TOKEN_NUM:
		return VT_num;
		break;
	case TOKEN_KEY:
		if (strcmp(token.word, "begin") == 0)
			return VT_begin;
		else if (strcmp(token.word, "end") == 0)
			return VT_end;
		else
			return 0;
		break;
	case TOKEN_GIVE:
		return VT_is;
		break;
	case TOKEN_SMCL:
		return VT_smcl;
		break;
	case TOKEN_OP:
		if (strcmp(token.word, "+") == 0)
			return VT_op_plu;
		else if (strcmp(token.word, "-") == 0)
			return VT_op_min;
		else if (strcmp(token.word, "*") == 0)
			return VT_op_mul;
		else if (strcmp(token.word, "/") == 0)
			return VT_op_div;
		else
			return 0;
		break;
	case TOKEN_BRCKT:
		if (strcmp(token.word, "(") == 0)
			return VT_lks;
		else if (strcmp(token.word, ")") == 0)
			return VT_rks;
		else
			return 0;
		break;
	default:
		return 0;
		break;
	}
}

int LL1_get_STACK_type() {
	int V = 0;
	if (stack_LL1.see(&stack_LL1, &V))
	{
		return V;
	}
	else
		return 0;
}