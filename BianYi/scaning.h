#pragma once

#include"hashtable.h"

#define	STATE_START		0
#define STATE_ALPHA		1
#define STATE_ID_KEY	2
#define STATE_ALNUM		3
#define STATE_ID		4
#define	STATE_NUM		5
#define STATE_INTEGER	6
#define STATE_LEFT		7
#define STATE_LE		8
#define STATE_NE		9
#define STATE_LT		10
#define STATE_EQ		11
#define STATE_RIGHT		12
#define STATE_GE		13
#define STATE_GT		14
#define STATE_PL		15
#define STATE_MI		16
#define STATE_MU		17
#define STATE_DI		18
#define STATE_COLON		19
#define STATE_IS		20
#define STATE_UND		21
#define STATE_SEMCOL	26
#define STATE_REAL		27

#define CHAR_UND	-1	//	UND
#define CHAR_ENTER	0	//	\n
#define	CHAR_ALPHA	1	//	[A-Za-z]
#define CHAR_NUM	2	//	[0-9]
#define CHAR_LEFT	3	//	<
#define CHAR_RIGHT	4	//	>
#define CHAR_EQUAL	5	//	=
#define CHAR_ADD	6	//	+
#define CHAR_MINUS	7	//	-
#define CHAR_DIV	8	//	/
#define CHAR_PRO	9	//	*
#define CHAR_COLON	10	//	:
#define CHAR_SPACE	11	//	' '
#define CHAR_DOT	12	//	.
#define CHAR_SEMCOL	13	//	;
#define CHAR_BRCKT	14	//	(){}[]

#define TOKEN_END	-1	//文件结尾
#define TOKEN_UND	0	//未定义
#define TOKEN_ID	1	//标识符
#define TOKEN_NUM	2	//无符号数
#define TOKEN_KEY	3	//关键字
#define TOKEN_CMP	4	//比较运算符
#define TOKEN_GIVE	5	//赋值
#define TOKEN_SMCL	6	//分号
#define TOKEN_OP	7	//运算符 + - * /
#define TOKEN_BRCKT	8	//括号 ()[]{}

typedef struct {
	char *word;
	int state;
	int scaning_col;
	int scaning_row;
}_TOKEN_STATE_;

typedef struct {
	char *word;
	int type;
	int scaning_col;
	int scaning_row;
}_TOKEN_TYPE_;
#define SIZEOF_TOKEN_TYPE (sizeof(_TOKEN_TYPE_))

typedef struct _TOKEN_LIST_
{
	_TOKEN_TYPE_ *tokens;
	int *mark;
	int length;
	int contain;
	void(*addToken)(struct _TOKEN_LIST_ *list, _TOKEN_TYPE_ *token);
	void(*rmvToken)(struct _TOKEN_LIST_ *list, _TOKEN_TYPE_ *token);
}_TOKEN_LIST_;
#define TOKEN_VARY_LIST_CONTAIN	1024

void token_list_init(_TOKEN_LIST_ *list, int contain);
void _list_add_token(_TOKEN_LIST_ *list, _TOKEN_TYPE_ *token);
void _list_rmv_token(_TOKEN_LIST_ *list, _TOKEN_TYPE_ *token);

_TOKEN_TYPE_ scaning_get_token();
void scaning_init(const char * filename);

