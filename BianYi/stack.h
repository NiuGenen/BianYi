#pragma once

typedef struct _STACK_{
	int *stack;
	int top;
	int contain;
	int (*push)(struct _STACK_ *stack, int value);
	int (*pop)(struct _STACK_ *stack, int*value);
	int (*see)(struct _STACK_ *stack, int*value);
}_STACK_;
#define STACK_CONTAIN	1024

void _stack_init(_STACK_ *stack,int contain);