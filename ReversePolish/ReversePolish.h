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
int top;

void Push(int n)
{
	if (top >= STACK_SIZE)
	{
		throw std::out_of_range("stack");
	}

	stack[top++] = n;
}

int Pop()
{
	if (top <= 0)
	{
		throw std::out_of_range("stack");
	}

	return stack[--top];
}

int Peek()
{
	if (top <= 0)
	{
		throw std::out_of_range("stack");
	}

	return stack[top - 1];
}
#pragma endregion

#pragma region 역 폴란드 표기법
char polish_result[80];

void Polish(char* str)
{
	int temp;
	char* result = polish_result;

	top = 0;
	
	while (true)
	{
		while (isspace(*str))
		{
			str++;
		}

		// 행의 마지막인 경우
		if (*str == '\0')
		{
			while (top > 0)
			{
				*result = Pop();
				if (*result == '(')
				{
					std::cout << "괄호 '('의 쌍이 올바르지 않습니다.\n";
					exit(1);
				}
				result++;
			}
			break;
		}

		// 문자나 숫자인 경우
		if (islower(*str) || isdigit(*str))
		{
			*result++ = *str++;
			continue;
		}

		switch (*str)
		{
		case '(':
			Push(*str);
			break;
		case ')':
			while (true)
			{
				temp = Pop();
				if (temp != '(')
				{
					*result++ = temp;
					if (top == 0)
					{
						std::cout << "괄호 '('의 쌍이 올바르지 않습니다.\n";
						exit(1);
					}
				}
			}
			break;
		default:
			if (Order(*result) == -1)
			{
				std::cout << "우선순위가 결정되지 않은 문자입니다.\n";
				exit(1);
			}

			while (top > 0 && Order(Peek()) >= Order(*str))
			{
				*result++ = Pop();
			}

			Push(*str);
			break;
		}
		str++;
	}
	*result = '\0';
}
#pragma endregion