#pragma once
#include "hash.h"

enum HashFunc
{
	SDBM,
	RS,
	JS,
	PJW,
	ELF,
	BKDR,
	DJB,
	AP
};

typedef struct _Hash_Node
{
	char * str;
	struct _Hash_Node * next;
}_Hash_Node;

typedef struct _Hash_Table {
	_Hash_Node **buckets;
	int length;
	unsigned int(*hashfunc)(char *str);
}_Hash_Table;

bool hash_table_create(unsigned int length, enum HashFunc hashfunc);
bool hash_insert(char *str);
struct _Hash_Node* hash_value(char *str);
bool hash_remove(char * str);

void _test_Hash_Table();