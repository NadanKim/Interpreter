#pragma once
#include <iostream>

#pragma region 우선순위 설정
int Order(const int ch)
{
	switch (ch)
	{
	case '*':
	case '/':
		return 3;
	case '+':
	case '-':
		return 2;
	case '(':
		return 1;
	}
	return -1;
}
#pragma endregion

#pragma region 스택 처리
#define STACK_SIZE 20

int stack[STACK_SIZE];
int stackHead;

void Push(int n)
{
	if (stackHead >= STACK_SIZE)
	{
		throw std::out_of_range("stack");
	}

	stack[stackHead++] = n;
}

int Pop()
{
	if (stackHead <= 0)
	{
		throw std::out_of_range("stack");
	}

	return stack[--stackHead];
}
#pragma endregion