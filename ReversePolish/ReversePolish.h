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
				else
				{
					break;
				}
			}
			break;
		default:
			if (Order(*str) == -1)
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

#pragma region 실행 처리
// a ~ z를 각각 변수이고 1 ~ 26이 저장되었다고 가정한다.
int GetValue(char ch)
{
	if (islower(ch))
	{
		return ch - 'a' + 1;
	}
	return 0;
}

int Execute()
{
	int num1, num2;
	char* str{ polish_result };

	top = 0;

	while(*str != '\0')
	{
		// 변수 처리
		if (islower(*str))
		{
			Push(GetValue(*str));
		}
		// 숫자 처리
		else if (isdigit(*str))
		{
			Push(*str - '0');
		}
		// 연산자 처리
		else
		{
			num2 = Pop();
			num1 = Pop();

			switch (*str)
			{
			case '+':
				Push(num1 + num2);
				break;
			case '-':
				Push(num1 - num2);
				break;
			case '*':
				Push(num1 * num2);
				break;
			case '/':
				if (num2 == 0)
				{
					std::cout << "0으로 나눌 수 없습니다.\n";
					exit(1);
				}
				Push(num1 / num2);
				break;
			}
		}

		str++;
	}
	
	// 결과가 제대로 저장되지 않은 경우
	if (top != 1)
	{
		std::cout << "결과가 존재하지 않습니다.\n";
		exit(1);
	}

	return Pop();
}
#pragma endregion