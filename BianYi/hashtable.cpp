#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Hash_Node
{
	char * str;
	struct _Hash_Node * next;
}_Hash_Node;

typedef struct _Hash_Table {
	_Hash_Node **buckets;
	int length;
	unsigned int (*hashfunc)(char *str);
}_Hash_Table;

_Hash_Table _hashtable;

#define SIZE_HASH_NODE (sizeof(_Hash_Node))
#define SIZE_HASH_TABLE (sizeof(_Hash_Table))

bool hash_table_create(unsigned int length, HashFunc hashfunc) {
	if (_hashtable.buckets != NULL) {
		free(_hashtable.buckets);
	}
	_hashtable.buckets = new _Hash_Node* [length];
	for (int i = 0; i < length; ++i) _hashtable.buckets[i] = NULL;

	if (_hashtable.buckets == NULL) {
		return false;
	}

	_hashtable.length = length;
	switch (hashfunc)
	{
	case SDBM:
		_hashtable.hashfunc = &SDBMHash;
		break;
	case RS:
		_hashtable.hashfunc = &RSHash;
		break;
	case JS:
		_hashtable.hashfunc = &JSHash;
		break;
	case PJW:
		_hashtable.hashfunc = &PJWHash;
		break;
	case ELF:
		_hashtable.hashfunc = &ELFHash;
		break;
	case BKDR:
		_hashtable.hashfunc = &BKDRHash;
		break;
	case DJB:
		_hashtable.hashfunc = &DJBHash;
		break;
	case AP:
		_hashtable.hashfunc = &APHash;
		break;
	default:
		_hashtable.hashfunc = &DJBHash;
		break;
	}

	return true;
}
bool hash_insert(char *str) {
	unsigned int hash_index = _hashtable.hashfunc(str) % _hashtable.length;
	int strlen = _mbstrlen(str);
	printf("Insert : %s	%d %d\n",str, hash_index, strlen);

	_Hash_Node * node = _hashtable.buckets[hash_index];
	if (node == NULL) {
		node = new _Hash_Node;
		_hashtable.buckets[hash_index] = node;
		printf("create hash node\n");
	}
	else {
		printf("Node != NULL\n");
		while (node->next != NULL) {
			if (strcmp(node->str, str) == 0) {
				return true;
			}
			node = node->next;
		}
		if (strcmp(node->str, str) == 0) {
			return true;
		}
		node->next = new _Hash_Node;
		node = node->next;
	}

	node->str = new char[strlen + 1];
	strcpy_s(node->str, strlen + 1, str);
	node->str[strlen] = '\0';
	node->next = NULL;
	return true;
}
_Hash_Node* hash_value(char *str) {
	unsigned int hash_index = (*(_hashtable.hashfunc))(str) % _hashtable.length;
	_Hash_Node * node = _hashtable.buckets[hash_index];
	if (node == NULL) {
		return NULL;
	}
	else {
		while (node != NULL) {
			if (strcmp(node->str, str) == 0) {
				return node;
			}
			node = node->next;
		}
	}
	return NULL;
}
bool hash_remove(char * str) {
	return true;
}

void _test_Hash_Table() {
	char *str = "int";
	if (hash_table_create(1024, SDBM)) {
		printf("Create_Hash_Table succeed!\n");
	}

	hash_insert("double");
	hash_insert(str);
	hash_insert("int");
	hash_insert("float");
	hash_insert("void");
	hash_insert("float");
	hash_insert("char");
	hash_insert("bool");
	hash_insert("unsigned");
	hash_insert("const");
	hash_insert("static");
	hash_insert("while");
	hash_insert("for");
	hash_insert("if");
	hash_insert("else");
	hash_insert("return");
	hash_insert("break");

	printf("%s	%d\n", "double", hash_value("double")==NULL?0:1);
	printf("%s	%d\n", "return", hash_value("return") == NULL ? 0 : 1);
	printf("%s	%d\n", "int", hash_value("int") == NULL ? 0 : 1);
	printf("%s	%d\n", "string", hash_value("string") == NULL ? 0 : 1);
	printf("%s	%d\n", "aacc", hash_value("aacc") == NULL ? 0 : 1);
}