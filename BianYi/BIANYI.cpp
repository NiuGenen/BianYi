#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include"scaning.h"
#include"stack.h"
#include"LL1G.h"

//scaning
const char *inputfile = "exp2.txt";
extern _TOKEN_LIST_ token_vary_list;
extern _TOKEN_LIST_ token_const_list;
_TOKEN_TYPE_ token;

//�ݹ��½��ӳ���
//ÿ���ӳ������֮ǰ�Ѷ�ȡһ��token
//ÿ���ӳ������������Զ���ȡ��һ��token
int MSP();			//MSP		->	<begin,KEY> STP() <end,KEY>
int STP();			//STP		->	SP()	STP_HELP()
int STP_HELP();		//STP_HELP	->	NULL | <;,SMCOL> STP()
int SP();			//SP		->	ISP()
int ISP();			//ISP		->	VP() <:=,IS> CP()
int CP();			//CP		->	IP() CP_HELP()
int CP_HELP();		//CP_HELP	->	NULL | <+,OP> CP() | <-,OP> CP()
int IP();			//IP		->	DP() IP_HELP()
int IP_HELP();		//IP_HELP	->	NULL | <*,OP> IP() | </,OP> IP()
int DP();			//DP		->	VP() | <num> | <(,BRCKT> CP() <),BRCKT>
int VP();			//VP		->	<ID>

//LL1�ķ�����
extern int ***matrix_LL1;
extern _STACK_ stack_LL1;

//���token��Ϣ
void printToken(_TOKEN_TYPE_ token);

int main()
{
	scaning_init(inputfile);

	////�ݹ��½�
	//token = scaning_get_token();
	//while (token.type != TOKEN_END) {
	//	if (MSP()) {
	//		continue;
	//	}
	//	else {
	//		printf("ERROR ");
	//		printToken(token);
	//		printf("\n");
	//		break;
	//	}
	//}

	//Ԥ�����
	ll1_g_init();//��ʼ��Ԥ�����

	int STR_head = 0;
	int STACK_top = 0;

	token = scaning_get_token();
	STR_head = LL1_get_STRING_type(token);
	
	int trash = 0;//��ջ����Ͱ
	while (token.type != TOKEN_END) {
		STACK_top = LL1_get_STACK_type();
		printf("[STACK]%3d [STRING]%3d\n", STACK_top, STR_head);

		if (STACK_top > 0) {//ջ��Ϊ�ս��
			if (STR_head != STACK_top) {//ջ���������ַ�������ͬ
				printf("ERROR ");
				printToken(token);//ʶ��ʧ��
				printf("\n");
				break;
			}
			else {//ջ���������ַ�����ͬ
				stack_LL1.pop(&stack_LL1,&trash);//����ջ��������Ͱ��
				token = scaning_get_token();//�������ַ�
				STR_head = LL1_get_STRING_type(token);
				continue;
			}
		}
		else //ջ��Ϊ���ս��
		{
			STACK_top = -STACK_top;
			int * product = matrix_LL1[STACK_top][STR_head];//���ݾ����ȡ����ʽ
			if (product == NULL) {//���޶�Ӧ����ʽ
				printf("ERROR ");
				printToken(token);//ʶ��ʧ��
				printf("\n");
				break;
			}
			else {
				stack_LL1.pop(&stack_LL1, &trash);//������ջ��
				for (int i = 0; product[i]; ++i) {
					stack_LL1.push(&stack_LL1, product[i]);//ѹ�����ʽ
				}
			}
		}
	}

	if (token.type == TOKEN_END) {
		printf("\n-----SUCCESS-----\n");
	}

	//������
	printf("\n-----VARY_LIST-----\n");
	for (int i = 0; i < token_vary_list.contain; ++i) {
		if (token_vary_list.mark[i] == 1) {
			printToken(token_vary_list.tokens[i]);
			printf("\n");
		}
	}
	printf("-----VARY_LIST----\n\n");

	//������
	printf("\n-----VARY_LIST-----\n");
	for (int i = 0; i < token_const_list.contain; ++i) {
		if (token_const_list.mark[i] == 1) {
			printToken(token_const_list.tokens[i]);
			printf("\n");
		}
	}
	printf("-----VARY_LIST----\n\n");

	system("pause");
}

int MSP() {
	//printf("MSP?\n");
	if (token.type != TOKEN_KEY || strcmp(token.word, "begin") != 0) {
		return 0;
	}

	token = scaning_get_token();
	if(STP()){
		if (token.type != TOKEN_KEY || strcmp(token.word, "end") != 0) {
			return 0;
		}
		token = scaning_get_token();
		//printf("MSP!\n");
		return 1;
	}
	return 0;
}

int STP() {
	//printf("STP?\n");
	if(SP()){
		if (token.type == TOKEN_SMCL){
			token = scaning_get_token();
			if(STP_HELP()){
				//token = scaning_get_token();
				//printf("STP!\n");
				return 1;
			}
		}
	}
	return 0;
}

int STP_HELP() {
	//printf("STP_HELP?\n");
	//if (token.type == TOKEN_SMCL) {
		//token = scaning_get_token();
		if(STP()){
			//token = scaning_get_token();
			//printf("STP_HELP!\n");
			return 1;
		}
		//else return 0;
	//}
	else {
		//token = scaning_get_token();
		return 1;
	}
}

int SP() {
	//printf("SP?\n");
	if(ISP()){
		//token = scaning_get_token();
		//printf("SP!\n");
		return 1;
	}
	else return 0;
}

int ISP() {
	//printf("ISP?\n");
	if(VP()){
		if (token.type == TOKEN_GIVE) {
			token = scaning_get_token();
			if(CP()){
				//token = scaning_get_token();
				//printf("ISP!\n");
				return 1;
			}
		}
	}
	return 0;
}

int CP() {
	//printf("CP?\n");
	if (IP()) {
		if (CP_HELP()) {
			//token = scaning_get_token();
			//printf("CP!\n");
			return 1;
		}
	}
	return 0;
}

int CP_HELP() {
	//printf("CP_HELP?\n");
	if (token.type == TOKEN_OP && (strcmp(token.word, "+") == 0|| strcmp(token.word, "-") == 0)) {
		token = scaning_get_token();
		if (CP()) {
			//token = scaning_get_token();
			//printf("CP_HELP!\n");
			return 1;
		}
		else {
			return 0;
		}
	}
	else return 1;
}

int IP() {
	//printf("IP?\n");
	if (DP()) {
		if (IP_HELP()) {
			//token = scaning_get_token();
			//printf("IP!\n");
			return 1;
		}
	}
	return 0;
}

int IP_HELP() {
	//printf("IP_HELP?!\n");
	if (token.type == TOKEN_OP && (strcmp(token.word, "*") == 0 || strcmp(token.word, "/") == 0)) {
		token = scaning_get_token();
		if (IP()) {
			//token = scaning_get_token();
			//printf("IP_HELP!\n");
			return 1;
		}
	}
	else return 1;
}

int DP() {
	//printf("DP?\n");
	if (token.type == TOKEN_NUM) {
		token = scaning_get_token();
		//printf("DP!\n");
		return 1;
	}
	if (VP()) {
		//token = scaning_get_token();
		//printf("DP!\n");
		return 1;
	}
	if (token.type == TOKEN_BRCKT && strcmp(token.word, "(") == 0) {
		token = scaning_get_token();
		if (CP()) {
			if (token.type == TOKEN_BRCKT && strcmp(token.word, ")") == 0) {
				token = scaning_get_token();
				//printf("DP!\n");
				return 1;
			}
		}
	}
	return 0;
}

int VP() {
	//printf("VP?\n");
	if (token.type == TOKEN_ID) {
		token = scaning_get_token();
		//printf("VP!\n");
		return 1;
	}
	return 0;
}

void printToken(_TOKEN_TYPE_ token) {
	printf("[%3d][%3d] %s",token.scaning_col,token.scaning_row, token.word);
}