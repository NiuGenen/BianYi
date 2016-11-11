#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include"scaning.h"

static FILE *in = NULL;

static int ifEOF() {
	if (!feof(in))
		return 0;
	else
		return 1;
}

#define UNDEFINE_CHAR "UND"
static char state_str[31][20] = { "KEY",
"",			"ID",	"",		"ID",	"",
"INTEGER",	"",		"LE",	"NE",	"LT",
"EQ",		"",		"GE",	"GT",	"PL",
"MI",		"MU",	"DI",	"",		"IS",
UNDEFINE_CHAR ,"",	"",		"",		"",
"SEMCOL" ,"REAL" ,	"",		"",		"BRCKT"};

#define KEY_WORD_NR	8
static char keywords[KEY_WORD_NR][20] = { "begin","end","if","else","then","while","for","goto" };

static int isKeyWord(char *str) {
	for (int i = 0; i < KEY_WORD_NR; ++i) {
		if (strcmp(str, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

static char *token_to_str(_TOKEN_STATE_ token) {
	if (token.state == STATE_ID_KEY && isKeyWord(token.word)) {
		token.state = 0;
	}
	if (strcmp(state_str[token.state], "") == 0) {
		return  NULL;
	}
	char *word_type = state_str[token.state];
	int token_len = strlen(token.word) + strlen(word_type) + 3;
	char *token_str = (char *)malloc(sizeof(char)*(token_len + 1));
	sprintf_s(token_str, token_len + 1, "<%s,%s>", token.word, word_type);
	return token_str;
}

_TOKEN_TYPE_ token_to_type(_TOKEN_STATE_ token) {
	_TOKEN_TYPE_ ret;
	ret.word = token.word;
	ret.scaning_col = token.scaning_col;
	ret.scaning_row = token.scaning_row;

	if (token.state == STATE_ID_KEY && isKeyWord(token.word)) {
		token.state = 0;
	}
	if (strcmp(state_str[token.state], "KEY") == 0) {
		ret.type = TOKEN_KEY;
	}
	else if (strcmp(state_str[token.state], "ID") == 0) {
		ret.type = TOKEN_ID;
	}
	else if (strcmp(state_str[token.state], "INTEGER") == 0 || strcmp(state_str[token.state], "REAL") == 0) {
		ret.type = TOKEN_NUM;
	}
	else if (strcmp(state_str[token.state], "LE") == 0 || strcmp(state_str[token.state], "NE") == 0 ||
		strcmp(state_str[token.state], "LT") == 0 || strcmp(state_str[token.state], "EQ") == 0 ||
		strcmp(state_str[token.state], "GE") == 0 || strcmp(state_str[token.state], "GT") == 0) {
		ret.type = TOKEN_CMP;
	}
	else if (strcmp(state_str[token.state], "PL") == 0 || strcmp(state_str[token.state], "MI") == 0 ||
		strcmp(state_str[token.state], "MU") == 0 || strcmp(state_str[token.state], "DI") == 0) {
		ret.type = TOKEN_OP;
	}
	else if (strcmp(state_str[token.state], "IS") == 0) {
		ret.type = TOKEN_GIVE;
	}
	else if (strcmp(state_str[token.state], "SEMCOL") == 0) {
		ret.type = TOKEN_SMCL;
	}
	else if (strcmp(state_str[token.state], "BRCKT") == 0) {
		ret.type = TOKEN_BRCKT;
	}
	else if (strcmp(state_str[token.state], "UND") == 0) {
		ret.type = TOKEN_UND;
	}

	printf("TOKEN:%s\n", token_to_str(token));

	return ret;
}

static int idChar(char c) {
	if (isalpha(c)) return CHAR_ALPHA;
	if (isdigit(c)) return CHAR_NUM;
	if (c == '<')	return CHAR_LEFT;
	if (c == '>')	return CHAR_RIGHT;
	if (c == '=')	return CHAR_EQUAL;
	if (c == '+')	return CHAR_ADD;
	if (c == '-')	return CHAR_MINUS;
	if (c == '*')	return CHAR_PRO;
	if (c == '/')	return CHAR_DIV;
	if (c == ':')	return CHAR_COLON;
	if (c == '\n')	return CHAR_ENTER;
	if (c == ' ')	return CHAR_SPACE;
	if (c == '.')	return CHAR_DOT;
	if (c == ';')	return CHAR_SEMCOL;
	if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}')	return CHAR_BRCKT;
	else return CHAR_UND;
}

_TOKEN_LIST_ token_vary_list;
static int token_vary_list_init = 0;

_TOKEN_LIST_ token_const_list;
static int token_const_list_init = 0;

static char scaning_char;
static char scaning_word[50] = { 0 };
static int scaning_word_pos = 0;

static int scanning_state = 0;

static int scaning_word_end_mark = 0;
static int scaning_need_this_char = 0;
static int scaning_cur_char_type = 0;
static int scanning_loop = 1;

static long scaning_offset = 0;
static int scaning_col = 1;
static int scaning_row = 1;

_TOKEN_TYPE_ scaning_get_token() 
{
	if (!token_vary_list_init) {
		token_list_init(&token_vary_list, TOKEN_VARY_LIST_CONTAIN);
		token_vary_list_init = 1;
	}
	if (!token_const_list_init) {
		token_list_init(&token_const_list, TOKEN_VARY_LIST_CONTAIN);
		token_const_list_init = 1;
	}

	fseek(in, scaning_offset, SEEK_SET);
	while (scanning_loop) {
		if (!scaning_need_this_char) {
			if (!ifEOF()) {
				if (!fread(&scaning_char, 1, 1, in)) {	//读过一次后才知道是否EOF
					scanning_loop = 0;
					scaning_char = '\n';
				}
			}
			else {
				scanning_loop = 0;
				scaning_char = '\n';
			}
		}
		else {
			scaning_need_this_char = 0;
		}
		scaning_cur_char_type = idChar(scaning_char);
		switch (scanning_state)
		{
		case STATE_START:
			if (scaning_cur_char_type == CHAR_DOT) {
				scanning_state = 28;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_BRCKT) {
				scanning_state = 30;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else if (scaning_cur_char_type == CHAR_SEMCOL) {
				scanning_state = STATE_SEMCOL;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else if (scaning_cur_char_type == CHAR_ALPHA) {
				scanning_state = STATE_ALPHA;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_NUM) {
				scanning_state = STATE_NUM;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_LEFT) {
				scanning_state = STATE_LEFT;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_RIGHT) {
				scanning_state = STATE_RIGHT;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_EQUAL) {
				scanning_state = STATE_EQ;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else if (scaning_cur_char_type == CHAR_ADD) {
				scanning_state = STATE_PL;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else if (scaning_cur_char_type == CHAR_MINUS) {
				scanning_state = STATE_MI;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else if (scaning_cur_char_type == CHAR_DIV) {
				scanning_state = STATE_DI;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else if (scaning_cur_char_type == CHAR_PRO) {
				scanning_state = STATE_MU;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else if (scaning_cur_char_type == CHAR_COLON) {
				scanning_state = STATE_COLON;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_ENTER || scaning_cur_char_type == CHAR_SPACE) {
				if (scaning_cur_char_type == CHAR_ENTER){
					++scaning_col;
					scaning_row = 1;
					//printf("\n");
				}
				continue;
			}
			else {
				scanning_state = STATE_UND;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			break;
		case STATE_ALPHA:
			if (scaning_cur_char_type == CHAR_ALPHA) {
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_NUM) {
				scanning_state = STATE_ALNUM;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else {
				scanning_state = STATE_ID_KEY;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case STATE_ALNUM:
			if (scaning_cur_char_type == CHAR_ALPHA || scaning_cur_char_type == CHAR_NUM) {
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else {
				scanning_state = STATE_ID;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case STATE_NUM:
			if (scaning_cur_char_type == CHAR_NUM) {
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_DOT) {
				scanning_state = 22;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_ALPHA && (scaning_char == 'e' || scaning_char == 'E')) {
				scanning_state = 23;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else {
				scanning_state = STATE_INTEGER;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case 22:
			if (scaning_cur_char_type == CHAR_NUM) {
				scanning_state = 25;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_ALPHA && (scaning_char == 'e' || scaning_char == 'E')) {
				scanning_state = 23;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else {
				scanning_state = STATE_INTEGER;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case 23:
			if (scaning_cur_char_type == CHAR_ADD || scaning_cur_char_type == CHAR_MINUS) {
				scanning_state = 24;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else if (scaning_cur_char_type == CHAR_NUM) {
				scanning_state = 25;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else {
				scanning_state = STATE_UND;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case 24:
			if (scaning_cur_char_type == CHAR_NUM) {
				scanning_state = 25;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else {
				scanning_state = STATE_UND;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case 25:
			if (scaning_cur_char_type == CHAR_NUM) {
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else {
				scanning_state = STATE_REAL;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case STATE_LEFT:
			if (scaning_cur_char_type == CHAR_EQUAL) {
				scanning_state = STATE_LE;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else if (scaning_cur_char_type == CHAR_RIGHT) {
				scanning_state = STATE_NE;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else {
				scanning_state = STATE_LT;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case STATE_RIGHT:
			if (scaning_cur_char_type == CHAR_EQUAL) {
				scanning_state = STATE_GE;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else {
				scanning_state = STATE_GT;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case STATE_COLON:
			if (scaning_cur_char_type == CHAR_EQUAL) {
				scanning_state = STATE_IS;
				scaning_word[scaning_word_pos++] = scaning_char;
				scaning_word_end_mark = 1;
			}
			else {
				scanning_state = STATE_UND;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case 28:
			if (scaning_cur_char_type == CHAR_NUM) {
				scanning_state = 29;
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else {
				scanning_state = STATE_UND;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
			break;
		case 29:
			if (scaning_cur_char_type == CHAR_NUM) {
				scaning_word[scaning_word_pos++] = scaning_char;
			}
			else {
				scanning_state = STATE_REAL;
				scaning_need_this_char = 1;
				scaning_word_end_mark = 1;
			}
		}

		if (scaning_word_end_mark) {
			scaning_word_end_mark = 0;

			int ret = 0;
			_TOKEN_STATE_ token;

			if (scaning_word_pos != 0) {
				scaning_word[scaning_word_pos] = '\0';
				int strlen_word = strlen(scaning_word) + 1;
				token.word = (char*)malloc(sizeof(char)*strlen_word);
				strcpy_s(token.word, strlen_word,scaning_word);
				token.state = scanning_state;
				token.scaning_col = scaning_col;
				token.scaning_row = scaning_row;
				scaning_row += 1;
				ret = 1;
				scaning_offset = ftell(in);
				//char *str = token_to_str(token);
				//if (str != NULL) {
				//	printf("%s", str);
				//}
			}
			if (scaning_cur_char_type == CHAR_ENTER || scaning_cur_char_type == CHAR_SPACE) {
				if(scaning_cur_char_type == CHAR_ENTER)
					++scaning_col;
				scaning_need_this_char = 0;
			}
			//if (char_type == CHAR_ENTER) {
			//	printf("\n");
			//}
			scanning_state = STATE_START;
			scaning_word_pos = 0;

			if (ret) {
				_TOKEN_TYPE_ _token = token_to_type(token);
				if(_token.type == TOKEN_ID)
					token_vary_list.addToken( &token_vary_list, &_token);
				else if(_token.type == TOKEN_NUM)
					token_const_list.addToken(&token_const_list, &_token);
				return _token;
			}
		}
	}

	static _TOKEN_TYPE_ nullret;
	nullret.word = NULL;
	nullret.type = TOKEN_END;
	return nullret;
}

void scaning_init(const char * filename) {
	fopen_s(&in, filename, "r");
	if (in == NULL) {
		printf("Open input file failed!\n");
		system("pause");
		exit(0);
	}
	//while (!feof(in)) {
	//	char c;
	//	fread(&c, 1, 1, in);
	//	putc(c, stdout);
	//}
	//pause();
	//exit(0);
}

void _list_add_token(_TOKEN_LIST_ *list, _TOKEN_TYPE_ *token) {
	for (int i = 0; i < list->contain; ++i) {
		if (list->mark[i] == 0) {
			list->mark[i] = 1;
			list->tokens[i] = *token;
			list->length += 1;
			break;
		}
	}
}

void _list_rmv_token(_TOKEN_LIST_ *list, _TOKEN_TYPE_ *token) {
	for (int i = 0; i < list->contain; ++i) {
		if (list->mark[i] == 1 && list->tokens[i].type == token->type && list->tokens[i].scaning_col == token->scaning_col && list->tokens[i].scaning_row == token->scaning_row &&
			strcmp(list->tokens[i].word, token->word) == 0) {
			list->mark[i] = 0;
			list->length -= 1;
		}
	}
}

void token_list_init(_TOKEN_LIST_ *list, int contain) {
	list->length = 0;
	list->contain = contain;
	list->tokens = (_TOKEN_TYPE_*)malloc(SIZEOF_TOKEN_TYPE*contain);
	list->mark = (int *)malloc(sizeof(int)*contain);
	memset(list->mark, 0, contain*sizeof(int));
	list->addToken = _list_add_token;
	list->rmvToken = _list_rmv_token;
}