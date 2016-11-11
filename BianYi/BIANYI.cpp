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

//递归下降子程序
//每个子程序进入之前已读取一个token
//每个子程序完成任务后自动读取下一个token
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

//LL1文法矩阵
extern int ***matrix_LL1;
extern _STACK_ stack_LL1;

//输出token信息
void printToken(_TOKEN_TYPE_ token);

int main()
{
	scaning_init(inputfile);

	////递归下降
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

	//预测分析
	ll1_g_init();//初始化预测矩阵

	int STR_head = 0;
	int STACK_top = 0;

	token = scaning_get_token();
	STR_head = LL1_get_STRING_type(token);
	
	int trash = 0;//出栈垃圾桶
	while (token.type != TOKEN_END) {
		STACK_top = LL1_get_STACK_type();
		printf("[STACK]%3d [STRING]%3d\n", STACK_top, STR_head);

		if (STACK_top > 0) {//栈顶为终结符
			if (STR_head != STACK_top) {//栈顶和输入字符串不相同
				printf("ERROR ");
				printToken(token);//识别失败
				printf("\n");
				break;
			}
			else {//栈顶和输入字符串相同
				stack_LL1.pop(&stack_LL1,&trash);//弹出栈顶到垃圾桶中
				token = scaning_get_token();//读入新字符
				STR_head = LL1_get_STRING_type(token);
				continue;
			}
		}
		else //栈顶为非终结符
		{
			STACK_top = -STACK_top;
			int * product = matrix_LL1[STACK_top][STR_head];//根据矩阵获取产生式
			if (product == NULL) {//若无对应产生式
				printf("ERROR ");
				printToken(token);//识别失败
				printf("\n");
				break;
			}
			else {
				stack_LL1.pop(&stack_LL1, &trash);//弹出旧栈顶
				for (int i = 0; product[i]; ++i) {
					stack_LL1.push(&stack_LL1, product[i]);//压入产生式
				}
			}
		}
	}

	if (token.type == TOKEN_END) {
		printf("\n-----SUCCESS-----\n");
	}

	//变量表
	printf("\n-----VARY_LIST-----\n");
	for (int i = 0; i < token_vary_list.contain; ++i) {
		if (token_vary_list.mark[i] == 1) {
			printToken(token_vary_list.tokens[i]);
			printf("\n");
		}
	}
	printf("-----VARY_LIST----\n\n");

	//常量表
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