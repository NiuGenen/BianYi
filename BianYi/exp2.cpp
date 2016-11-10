//#include<stdio.h>
//#include<Windows.h>
//#include<stdlib.h>
//#include<string.h>
//
//#include"scaning.h"
//
//const char *inputfile = "exp2.txt";
//FILE *in = NULL;
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
//int ifEOF() {
//	if (!feof(in))
//		return 0;
//	else
//		return 1;
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
//			if (!ifEOF()) {
//				if (!fread(&c, 1, 1, in)) {	//读过一次后才知道是否EOF
//					c = '\n';
//					loop = 0;
//				}
//			}
//			else {
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
//			if (char_type == CHAR_DOT) {
//				state = 28;
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_SEMCOL) {
//				state = STATE_SEMCOL;
//				word[pos++] = c;
//				word_end_mark = 1;
//			}
//			else if (char_type == CHAR_ALPHA) {
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
//				if (char_type == CHAR_ENTER)
//					printf("\n");
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
//			else if (char_type == CHAR_DOT) {
//				state = 22;
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_ALPHA && (c == 'e' || c == 'E')) {
//				state = 23;
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_INTEGER;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case 22:
//			if (char_type == CHAR_NUM) {
//				state = 25;
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_ALPHA && (c == 'e' || c == 'E')) {
//				state = 23;
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_INTEGER;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case 23:
//			if (char_type == CHAR_ADD || char_type == CHAR_MINUS) {
//				state = 24;
//				word[pos++] = c;
//			}
//			else if (char_type == CHAR_NUM) {
//				state = 25;
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_UND;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case 24:
//			if (char_type == CHAR_NUM) {
//				state = 25;
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_UND;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case 25:
//			if (char_type == CHAR_NUM) {
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_REAL;
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
//		case 28:
//			if (char_type == CHAR_NUM) {
//				state = 29;
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_UND;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//			break;
//		case 29:
//			if (char_type == CHAR_NUM) {
//				word[pos++] = c;
//			}
//			else {
//				state = STATE_REAL;
//				need_this_char = 1;
//				word_end_mark = 1;
//			}
//		}
//
//		if (word_end_mark) {
//			word_end_mark = 0;
//
//			if (pos != 0) {
//				word[pos] = '\0';
//				_TOKEN_STATE_ token;
//				token.word = word;
//				token.state = state;
//
//				char *str = token_to_str(token);
//				if (str != NULL) {
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