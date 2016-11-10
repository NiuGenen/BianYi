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

bool hash_table_create(unsigned int length, enum HashFunc hashfunc);
bool hash_insert(char *str);
struct _Hash_Node* hash_value(char *str);
bool hash_remove(char * str);

void _test_Hash_Table();