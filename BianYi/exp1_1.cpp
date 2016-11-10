//#include<stdio.h>
//#include<Windows.h>
//#include<stdlib.h>
//#include<string.h>
//
//#define	STATE_START		0
//#define STATE_ALPHA		1
//#define STATE_ID_KEY	2
//#define STATE_ALNUM		3
//#define STATE_ID		4
//#define	STATE_NUM		5
//#define STATE_INT		6
//#define STATE_LEFT		7
//#define STATE_LE		8
//#define STATE_NE		9
//#define STATE_LT		10
//#define STATE_EQ		11
//#define STATE_RIGHT		12
//#define STATE_GE		13
//#define STATE_GT		14
//#define STATE_PL		15
//#define STATE_MI		16
//#define STATE_MU		17
//#define STATE_DI		18
//#define STATE_COLON		19
//#define STATE_IS		20
//#define STATE_UND		21
//
//const char *inputfile = "exp1.txt";
//FILE *in = NULL;
//
//char keywords[5][20] = { "begin","end","if","else","then" };
//#define KEY_WORD_NR	5
//static int isKeyWord(char *str) {
//	for (int i = 0; i < KEY_WORD_NR; ++i) {
//		if (strcmp(str, keywords[i]) == 0)
//			return 1;
//	}
//	return 0;
//}
//
//#define UNDEFINE_CHAR "UND"
//char state_str[22][20] = { "KEY",
//"",		"ID",	"",		"ID",	"",
//"INT",	"",		"LE",	"NE",	"LT",
//"EQ",	"",		"GE",	"GT",	"PL",
//"MI",	"MU",	"DI",	"",		"IS",
//UNDEFINE_CHAR };
//
//void pause() {
//	system("pause");
//}
//
//void init(int test) {
//	fopen_s(&in, inputfile, "r");
//	if (in == NULL) {
//		printf("Open input file failed!\n");
//		pause();
//		exit(0);
//	}
//	if (test) {
//		while (!feof(in)) {
//			char c;
//			fread(&c, 1, 1, in);
//			putc(c, stdout);
//		}
//		pause();
//		exit(0);
//	}
//}
//
//typedef struct {
//	char *word;
//	int state;
//}_TOKEN;
//
//char *token_to_str(_TOKEN token) {
//	if (token.state == STATE_ID_KEY && isKeyWord(token.word)) {
//		token.state = 0;
//	}
//	if (strcmp(state_str[token.state], "") == 0) {
//		return  NULL;
//	}
//	char *word_type = state_str[token.state];
//	int token_len = strlen(token.word) + strlen(word_type) + 3;
//	char *token_str = (char *)malloc(sizeof(char)*(token_len + 1));
//	sprintf_s(token_str, token_len + 1, "<%s,%s>", token.word, word_type);
//	return token_str;
//}
//
//int ifEOF() {
//	if (!feof(in))
//		return 0;
//	else
//		return 1;
//}
//
//#define CHAR_ENTER	0	//	\n
//#define	CHAR_ALPHA	1	//	[A-Za-z]
//#define CHAR_NUM	2	//	[0-9]
//#define CHAR_LEFT	3	//	<
//#define CHAR_RIGHT	4	//	>
//#define CHAR_EQUAL	5	//	=
//#define CHAR_ADD	6	//	+
//#define CHAR_MINUS	7	//	-
//#define CHAR_DIV	8	//	/
//#define CHAR_PRO	9	//	*
//#define CHAR_COLON	10	//	:
//#define CHAR_SPACE	11	//	' '
//
//int idChar(char c) {
//	if (isalpha(c)) return CHAR_ALPHA;
//	if (isdigit(c)) return CHAR_NUM;
//	if (c == '<')	return CHAR_LEFT;
//	if (c == '>')	return CHAR_RIGHT;
//	if (c == '=')	return CHAR_EQUAL;
//	if (c == '+')	return CHAR_ADD;
//	if (c == '-')	return CHAR_MINUS;
//	if (c == '*')	return CHAR_PRO;
//	if (c == '/')	return CHAR_DIV;
//	if (c == ':')	return CHAR_COLON;
//	if (c == '\n')	return CHAR_ENTER;
//	if (c == ' ')	return CHAR_SPACE;
//}
//
//int main()
//{
//	init(0);
//
//	char c;
//	char word[50] = { 0 };
//	int pos = 0;
//
//	int state = 0;
//
//	int word_end_mark = 0;
//	int need_this_char = 0;
//	int char_type = 0;
//	int loop = 1;
//	while (loop) {
//		if (!need_this_char) {
//			//c = getChar();
//			if (!ifEOF()){
//				if (!fread(&c, 1, 1, in)) {	//读过一次后才知道是否EOF
//					c = '\n';
//					loop = 0;
//				}
//			}
//			else{
//				c = '\n';
//				loop = 0;
//			}
//		}
//		else {
//			need_this_char = 0;
//		}
//		char_type = idChar(c);
//		switch (state)
//		{
//		case STATE_START:
//			if (char_type == CHAR_ALPHA) {
//				state = STATE_ALPHA;
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_NUM) {
//				state = STATE_NUM;
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_LEFT) {
//				state = STATE_LEFT;
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_RIGHT) {
//				state = STATE_RIGHT;
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_EQUAL) {
//				state = STATE_EQ;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else if (char_type == CHAR_ADD) {
//				state = STATE_PL;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else if (char_type == CHAR_MINUS) {
//				state = STATE_MI;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else if (char_type == CHAR_DIV) {
//				state = STATE_DI;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else if (char_type == CHAR_PRO) {
//				state = STATE_MU;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else if (char_type == CHAR_COLON) {
//				state = STATE_COLON;
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_ENTER || char_type == CHAR_SPACE) {
//				continue;
//			}
//			else {
//				state = STATE_UND;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			break;
//		case STATE_ALPHA:
//			if (char_type == CHAR_ALPHA) {
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_NUM) {
//				state = STATE_ALNUM;
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_ID_KEY;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case STATE_ALNUM:
//			if (char_type == CHAR_ALPHA || char_type == CHAR_NUM) {
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_ID;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case STATE_NUM:
//			if (char_type == CHAR_NUM) {
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_INT;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case STATE_LEFT:
//			if (char_type == CHAR_EQUAL) {
//				state = STATE_LE;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else if (char_type == CHAR_RIGHT) {
//				state = STATE_NE;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else {
//				state = STATE_LT;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case STATE_RIGHT:
//			if (char_type == CHAR_EQUAL) {
//				state = STATE_GE;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else {
//				state = STATE_GT;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case STATE_COLON:
//			if (char_type == CHAR_EQUAL) {
//				state = STATE_IS;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else {
//				state = STATE_UND;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		}
//
//		if (word_end_mark) {
//			word_end_mark = 0;
//
//			if (pos != 0) {
//				word[pos] = '\0';
//				_TOKEN token;
//				token.word = word;
//				token.state = state;
//
//				char *str = token_to_str(token);
//				if (str != NULL){
//					printf("%s", str);
//				}
//			}
//			if (char_type == CHAR_ENTER || char_type == CHAR_SPACE) {
//				need_this_char = 0;
//			}
//			if (char_type == CHAR_ENTER) {
//				printf("\n");
//			}
//
//			state = STATE_START;
//			pos = 0;
//		}
//	}
//
//	pause();
//}