//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <string.h>
//#include "hashtable.h"
//
//enum TokenType {	//token的类型定义
//	TOKEN_IDENTITY = 1,		//标识符
//	TOKEN_OPERATION = 2,	//操作符	/1/ +- * / =  /2/ ++ -- /3/ < >
//	TOKEN_NUMBER = 4,		//整数
//	TOKEN_OTHERS = 8,		//其他		/1/ , ; ( ) { }
//	TOKEN_KEYWORD = 16		//关键字
//};
//
//const char * inputFile = "input.txt";
//const char * outputFile = "output.txt";
//
//struct token {	//token结构体
//	char *word;		//string
//	int type;		//类型
//};
//
//FILE * input;		//输入文件
//FILE * output;		//输出文件
//token *retToken;	//当前token
//
//const unsigned int buffer_len = 256;	//每次读取256个字符
//
///* 版本1 */
//// + - * / =
//// , ;
//// 1 2 3 4 5 6 7 8 9 0
//// _
//// a b c d ... x y z
////标识符：下划线or字母开头，后面为下划线、字母或数字
////数字：数字开头，后面全为数字
//
///* 版本2 */
////支持关键字，哈希表存储，可用户自定义
////识别++和--，即自增和自减
//
//void init() {	//全局初始化
//	int err = 1;
//	err = fopen_s(&input, inputFile, "r");//打开输入文件
//	if (err == 0) {
//		printf("Open input!\n");
//	}
//	else {
//		printf("Cannot open input!\n");
//		system("pause");
//		exit(0);
//	}
//	err = fopen_s(&output,outputFile, "w");//打开输出文件
//	if (err == 0) {
//		printf("Open output!\n");
//	}
//	else {
//		printf("Cannot open output!\n");
//		system("pause");
//		exit(0);
//	}
//	retToken = (token*)malloc(sizeof(token));//申请临时token空间
//	retToken->word = NULL;
//	
//}
//
//enum CharType {			//单个字符的类型
//	CHAR_WRONG = buffer_len,//无法识别
//	CHAR_ALPHA = 0,			//字母
//	CHAR_NUM = 1,			//数字
//	CHAR_UNDERLINE = 2,		//下划线
//	CHAR_SPACE = 3,			//空格、水平制表符
//	CHAR_ENTER = 4,			//回车
//	CHAR_COMMA = 5,			//逗号
//	CHAR_SEMICOLON = 6,		//分号
//	CHAR_OPERA = 7,			//操作符
//	CHAR_DOT = 8,			//小数点、成员运算符
//	CHAR_KEYWORD = 9,		//关键字定义#
//	CHAR_SMALL_LEFT = 10,	//左小括号
//	CHAR_SMALL_RIGHT = 11,	//右小括号
//	CHAR_BIG_LEFT = 12,		//左大括号
//	CHAR_BIG_RIGHT = 13,	//右大括号
//};
//
//CharType check(char c) {		//判断单个字符
//	if (isalpha(c))
//		return CHAR_ALPHA;
//
//	else if (isalnum(c))
//		return CHAR_NUM;
//
//	else if (c == '_')
//		return CHAR_UNDERLINE;
//
//	else if (c == ' ' || c == '\t')
//		return CHAR_SPACE;
//
//	else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '>' || c == '<')
//		return CHAR_OPERA;
//
//	else if (c == ')')
//		return CHAR_SMALL_LEFT;
//
//	else if (c == '(')
//		return CHAR_SMALL_RIGHT;
//
//	else if (c == '{')
//		return CHAR_BIG_LEFT;
//
//	else if (c == '}')
//		return CHAR_BIG_RIGHT;
//
//	else if (c == ';' || c == ',')
//		return CHAR_COMMA;
//
//	else if (c == '\n')
//		return CHAR_ENTER;
//
//	else if (c == '#')
//		return CHAR_KEYWORD;
//
//	else
//		return CHAR_WRONG;
//}
//
//char* tokenToStr(token *t) {	//token转换为str
//	char *str = (char*)malloc(128+32);
//	int strP = 0;
//	str[strP++] = '<';
//	while (t->word[strP - 1] != '\0') {
//		str[strP++] = t->word[strP - 1];
//	}
//	str[strP++] = ',';
//	switch (t->type)
//	{
//	case TOKEN_IDENTITY:	//标识符
//		str[strP++] = 'i';
//		str[strP++] = 'd';
//		break;
//	case TOKEN_OPERATION:	//操作符
//		str[strP++] = 'o';
//		str[strP++] = 'p';
//		break;
//	case TOKEN_NUMBER:		//整数
//		str[strP++] = 'n';
//		str[strP++] = 'u';
//		str[strP++] = 'm';
//		break;
//	case TOKEN_KEYWORD:		//关键字
//		str[strP++] = 'k';
//		str[strP++] = 'e';
//		str[strP++] = 'y';
//		break;
//	case TOKEN_OTHERS:		//其他
//		str[strP++] = 'o';
//		str[strP++] = 't';
//		str[strP++] = 'h';
//		break;
//	}
//	str[strP++] = '>';
//	str[strP] = '\0';
//	return str;
//}
//
//void close() {	//关闭文件
//	fclose(input);
//	fclose(output);
//}
//
//void Function()
//
//{
//
//	printf("Call Function!\n");
//
//}
//
//void print1() {
//	printf("1\n");
//}
//
//void print2() {
//	printf("2\n");
//}
//
//int main()
//{
//	void (*p)();
//
//	p = &Function;
//
//	printf("p:%d\n", (int)p);
//	printf("&p:%d\n", (int)(&p));
//	printf("Function:%d\n", (int)Function);
//	printf("Function:%d\n", (int)(&Function));
//
//	*(int*)&p = (int)Function;
//
//	(*p)();
//
//	printf("p:%d\n", (int)p);
//	printf("&p:%d\n", (int)(&p));
//	printf("Function:%d\n", (int)Function);
//	printf("Function:%d\n", (int)(&Function));
//
//	(*(void(*)())(int)Function)();
//	( (void(*)()) ((int)Function) )();
//
//	void (*ps[2])();
//
//	ps[0] = print1;
//	ps[1] = &print2;
//
//	ps[0]();
//	(*(ps[1]))();
//
//	void (*(*psp)[2])();
//	psp = &ps;
//
//	psp[0][0]();
//	(*psp)[1]();
//
//	int a[3];
//	printf("a:	%d\n", (int)a);
//	printf("&a:	%d\n", (int)(&a));
//
//	system("pause");
//
//	return 0;
//
//}
//
//int main2()
//{
//	//_test_Hash_Table();
//	hash_table_create(1024, DJB);
//
//	init();
//
//	int type = TOKEN_IDENTITY;
//	char *word = (char *)malloc(sizeof(char) * 128);		//最长128个字符
//	int wordPos = 0;
//
//	char *buffer = (char *)malloc(sizeof(char) * buffer_len + 1);	//读取缓存区
//	int readlen = 0;
//
//	int lineCount = 1;	//行数计数
//
//	int KeyWordDef = 0;
//	int wordEnd = 0;
//	int ifAlpha = 0;
//	int if_ = 0;
//	int ifNum = 0;
//
//	while ((readlen = fread(buffer, 1, buffer_len, input)) != 0) {
//
//		printf("------------%d------------\n", readlen);
//		buffer[readlen] = '\0';
//		printf("%s\n", buffer);
//		printf("--------------------------\n");
//
//		for (int i = 0; i < readlen; ++i) {
//			char c = buffer[i];
//			CharType char_type = check(c);
//			switch (char_type)
//			{
//			case CHAR_KEYWORD:
//				KeyWordDef = 1;
//				break;
//			case CHAR_ENTER:
//				++lineCount;
//				wordEnd = 1;
//				if(!KeyWordDef) fwrite("\n", 1, 1, output);
//				break;
//
//			case CHAR_ALPHA:
//				ifAlpha = 1;
//				break;
//
//			case CHAR_UNDERLINE:
//				if_ = 1;
//				break;
//
//			case CHAR_NUM:
//				ifNum = 1;
//				break;
//
//			case CHAR_SPACE:
//			case CHAR_OPERA:
//			case CHAR_COMMA:
//			case CHAR_SEMICOLON:
//			case CHAR_SMALL_LEFT:
//			case CHAR_SMALL_RIGHT:
//			case CHAR_BIG_LEFT:
//			case CHAR_BIG_RIGHT:
//				wordEnd = 1;
//				break;
//
//			case CHAR_WRONG:
//				printf("Undefined charactor\n");
//				goto OVER;
//				break;
//			}
//
//			if (ifAlpha == 1 || if_ == 1) {
//				ifAlpha = 0;
//				if_ = 0;
//				if (wordPos == 0) {
//					type = TOKEN_IDENTITY;
//					word[wordPos++] = c;
//				}
//				else {
//					if (type == TOKEN_IDENTITY) {
//						word[wordPos++] = c;
//					}
//					else {
//						printf("Line[%d]: Wrong inentity!\n", lineCount);
//						goto OVER;
//					}
//				}
//			}
//
//			if (ifNum == 1) {
//				ifNum = 0;
//				if (wordPos == 0) {
//					type = TOKEN_NUMBER;
//					word[wordPos++] = c;
//				}
//				else {
//					if (type == TOKEN_NUMBER || type == TOKEN_IDENTITY) {
//						word[wordPos++] = c;
//					}
//					else {
//						printf("Line[%d]: Wrong inentity!\n", lineCount);
//						goto OVER;
//					}
//				}
//			}
//
//			if (wordEnd == 1) {
//				wordEnd = 0;
//				if (wordPos != 0) {
//					word[wordPos] = '\0';
//					if (!KeyWordDef) {
//						retToken->word = word;
//						if (hash_value(word))
//							retToken->type = TOKEN_KEYWORD;
//						else 
//							retToken->type = type;
//						char *str = tokenToStr(retToken);
//						printf("%s\n", str);
//						fwrite(str, 1, strlen(str) + 1, output);
//					}
//					else
//					{
//						hash_insert(word);
//						KeyWordDef = 0;
//					}
//				}
//				wordPos = 0;
//				if (char_type != CHAR_SPACE && char_type != CHAR_ENTER) {	
//					//单词结束符ENTER、SPACE 不被识别，其余的被识别
//
//					retToken->word[wordPos++] = c;
//					if (char_type == CHAR_OPERA && (c == '+' || c == '-')) {	//+ 或 -
//						if ((i+1) <= buffer_len && c == buffer[i+1]) {
//							++i;
//							retToken->word[wordPos++] = c;	//识别++和--
//						}
//					}
//					retToken->word[wordPos] = '\0';
//
//					if (char_type == CHAR_OPERA)
//						retToken->type = TOKEN_OPERATION;
//					else
//						retToken->type = TOKEN_OTHERS;
//
//					char *str = tokenToStr(retToken);
//					printf("%s\n", str);
//					fwrite(str, 1, strlen(str) + 1, output);
//					wordPos = 0;
//
//					if (char_type == CHAR_SEMICOLON) {	//分号则向输出文件输出换行符
//						fwrite("\n", 1, 1, output);
//					}
//				}
//			}
//
//		}
//	}
//
//OVER:
//	close();
//	system("pause");
//	return 0;
//}