#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum TokenType {
	TYPE_INENTITY = 1,
	TYPE_OPERATION = 2,
	TYPE_NUMBER = 4,
	TYPE_OTHERS = 8
};

const char * inputFile = "input.txt";
const char * outputFile = "output.txt";

struct token {
	char *word;
	int type;
};

FILE * input;
FILE * output;
token *retToken;

int str_len = 8;

// + - * / =
// , ;
// 1 2 3 4 5 6 7 8 9 0
// _
// a b c d ... x y z
//标识符：下划线or字母开头，后面为下划线、字母或数字
//数字：数字开头，后面全为数字

void init() {
	int err = 1;
	err = fopen_s(&input, inputFile, "r");
	if (err == 0) {
		printf("Open input!\n");
	}
	else {
		printf("Cannot open input!\n");
		system("pause");
		exit(0);
	}
	err = fopen_s(&output,outputFile, "w");
	if (err == 0) {
		printf("Open output!\n");
	}
	else {
		printf("Cannot open output!\n");
		system("pause");
		exit(0);
	}
	retToken = (token*)malloc(sizeof(token));
	retToken->word = NULL;
}

int check(char c) {
	if (isalpha(c))
		return 1;
	else if (isalnum(c))
		return 2;
	else if (c == '_')
		return 3;
	else if (c == ' ')
		return -1;
	else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=')
		return -2;
	else if (c == ';' || c == ',')
		return -3;
	else if (c == '\n')
		return 0;
	else
		return 128;
}

char* tokenToStr(token *t) {
	char *str = (char*)malloc(128+32);
	int strP = 0;
	str[strP++] = '<';
	while (t->word[strP - 1] != '\0') {
		str[strP++] = t->word[strP - 1];
	}
	str[strP++] = ',';
	switch (t->type)
	{
	case TYPE_INENTITY:
		str[strP++] = 'i';
		str[strP++] = 'd';
		break;
	case TYPE_OPERATION:
		str[strP++] = 'o';
		str[strP++] = 'p';
		break;
	case TYPE_NUMBER:
		str[strP++] = 'n';
		str[strP++] = 'u';
		str[strP++] = 'm';
		break;
	case TYPE_OTHERS:
		str[strP++] = 'o';
		str[strP++] = 't';
		str[strP++] = 'h';
		break;
	}
	str[strP++] = '>';
	str[strP] = '\0';
	return str;
}

void close() {
	fclose(input);
	fclose(output);
}

int main()
{
	init();

	int type = TYPE_INENTITY;
	char *word = (char *)malloc(sizeof(char) * 128);
	int wordP = 0;

	char *str = (char *)malloc(sizeof(char) * str_len + 1);
	int len = 0;

	int lineCount = 1;

	int ifcon = 0;
	int wordEnd = 0;
	int if_Alpha = 0;
	int ifNum = 0;

	while ((len = fread(str, 1, str_len, input)) != 0) {

		printf("------------%d------------\n", len);
		str[len] = '\0';
		printf("%s\n", str);
		printf("--------------------------\n");

		for (int i = 0; i < len; ++i) {
			char c = str[i];
			switch (check(c))
			{
			case 0://\n
				++lineCount;
				ifcon = 1;
				break;
			case 1://letter
			case 3://'_'
				if_Alpha = 1;
				break;
			case 2://num
				ifNum = 1;
				break;
			case -1://' '
			case -2://operation
			case -3://, ; -> others
				wordEnd = 1;
				break;
			case 128://undefined charactor
				printf("Undefined charactor\n");
				goto OVER;
				break;
			}

			if (ifcon == 1) {
				ifcon = 0;
				continue;
			}
			if (if_Alpha == 1) {
				if_Alpha = 0;
				if (wordP == 0) {
					type = TYPE_INENTITY;
					word[wordP++] = c;
				}
				else {
					if (type == TYPE_INENTITY) {
						word[wordP++] = c;
					}
					else {
						printf("Line[%d]: Wrong inentity!\n", lineCount);
						goto OVER;
					}
				}
			}
			if (ifNum == 1) {
				ifNum = 0;
				if (wordP == 0) {
					type = TYPE_NUMBER;
					word[wordP++] = c;
				}
				else {
					if (type == TYPE_NUMBER || type == TYPE_INENTITY) {
						word[wordP++] = c;
					}
					else {
						goto OVER;
					}
				}
			}
			if (wordEnd == 1) {
				wordEnd = 0;
				if (wordP != 0) {
					word[wordP] = '\0';
					retToken->word = word;
					retToken->type = type;
					char *str = tokenToStr(retToken);
					printf("%s\n", str);
					fwrite(str, 1, strlen(str) + 1, output);
				}
				wordP = 0;
				if (c != ' ') {
					retToken->word[wordP++] = c;
					retToken->word[wordP] = '\0';
					if (c == ',' || c == ';')
						retToken->type = TYPE_OTHERS;
					else
						retToken->type = TYPE_OPERATION;
					char *str = tokenToStr(retToken);
					printf("%s\n", str);
					fwrite(str, 1, strlen(str) + 1, output);
					wordP = 0;

					if (c == ';') {
						fwrite("\n", 1, 1, output);
					}
				}
			}
		}
	}

OVER:
	close();
	system("pause");
	return 0;
}