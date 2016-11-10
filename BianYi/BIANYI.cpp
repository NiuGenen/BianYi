#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include"scaning.h"

const char *inputfile = "exp2.txt";

_TOKEN_TYPE_ token;

//每个子程序进入之前第一个token已读取
//每个子程序退出后自动读入下一个token

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

int main()
{
	scaning_init(inputfile);

	token = scaning_get_token();
	while (token.type != TOKEN_END) {
		if (MSP()) {
			continue;
		}
		else {
			printf("WRONG!\nTOKEN: %s",token.word);
			break;
		}
	}

	system("pause");
}

int MSP() {
	printf("MSP?\n");
	if (token.type != TOKEN_KEY || strcmp(token.word, "begin") != 0)
		return 0;

	token = scaning_get_token();
	if(STP()){
		if (token.type != TOKEN_KEY || strcmp(token.word, "end") != 0)
			return 0;
		token = scaning_get_token();
		printf("MSP!\n");
		return 1;
	}
	return 0;
}

int STP() {
	printf("STP?\n");
	if(SP()){

		if(STP_HELP()){

			//token = scaning_get_token();

			printf("STP!\n");
			return 1;
		}
	}
	return 0;
}

int STP_HELP() {
	printf("STP_HELP?\n");
	if (token.type == TOKEN_SMCL) {
		token = scaning_get_token();
		if(STP()){
			//token = scaning_get_token();
			printf("STP_HELP!\n");
			return 1;
		}
		else return 0;
	}
	else {
		//token = scaning_get_token();
		return 1;
	}
}

int SP() {
	printf("SP?\n");
	if(ISP()){
		//token = scaning_get_token();
		printf("SP!\n");
		return 1;
	}
	else return 0;
}

int ISP() {
	printf("ISP?\n");
	if(VP()){
		if (token.type == TOKEN_GIVE) {
			token = scaning_get_token();
			if(CP()){
				//token = scaning_get_token();
				printf("ISP!\n");
				return 1;
			}
		}
	}
	return 0;
}

int CP() {
	printf("CP?\n");
	if (IP()) {
		if (CP_HELP()) {
			//token = scaning_get_token();
			printf("CP!\n");
			return 1;
		}
	}
	return 0;
}

int CP_HELP() {
	printf("CP_HELP?\n");
	if (token.type == TOKEN_OP && (strcmp(token.word, "+") == 0|| strcmp(token.word, "-") == 0)) {
		token = scaning_get_token();
		if (CP()) {
			//token = scaning_get_token();
			printf("CP_HELP!\n");
			return 1;
		}
	}
	else return 1;
}

int IP() {
	printf("IP?\n");
	if (DP()) {
		if (IP_HELP()) {
			//token = scaning_get_token();
			printf("IP!\n");
			return 1;
		}
	}
	return 0;
}

int IP_HELP() {
	printf("IP_HELP?!\n");
	if (token.type == TOKEN_OP && (strcmp(token.word, "*") == 0 || strcmp(token.word, "/") == 0)) {
		token = scaning_get_token();
		if (IP()) {
			//token = scaning_get_token();
			printf("IP_HELP!\n");
			return 1;
		}
	}
	else return 1;
}

int DP() {
	printf("DP?\n");
	if (token.type == TOKEN_NUM) {
		token = scaning_get_token();
		printf("DP!\n");
		return 1;
	}
	if (VP()) {
		//token = scaning_get_token();
		printf("DP!\n");
		return 1;
	}
	if (token.type == TOKEN_BRCKT && strcmp(token.word, "(") == 0) {
		token = scaning_get_token();
		if (CP()) {
			if (token.type == TOKEN_BRCKT && strcmp(token.word, ")") == 0) {
				token = scaning_get_token();
				printf("DP!\n");
				return 1;
			}
		}
	}
	return 0;
}

int VP() {
	printf("VP?\n");
	if (token.type == TOKEN_ID) {
		token = scaning_get_token();
		printf("VP!\n");
		return 1;
	}
	return 0;
}