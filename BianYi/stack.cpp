#include"stack.h"
#include<stdlib.h>

int _stack_push(_STACK_ *stack, int value) {
	if (stack->top < stack->contain) {
		stack->top += 1;
		stack->stack[stack->top] = value;
		return 1;
	}
	else return 0;
}

int _stack_pop(_STACK_ *stack, int *value) {
	if (stack->top >= 0) {
		*value = stack->stack[stack->top];
		stack->top -= 1;
		return 1;
	}
	else return 0;
}

int _stack_see(_STACK_ *stack, int *value) {
	if (stack->top >= 0) {
		*value = stack->stack[stack->top];
		return 1;
	}
	else return 0;
}

void _stack_init(_STACK_ *stack, int contain){
	stack->contain = contain;
	stack->top = -1;
	stack->stack = (int*)malloc(sizeof(int)*contain);
	stack->push = _stack_push;
	stack->pop = _stack_pop;
	stack->see = _stack_see;
}