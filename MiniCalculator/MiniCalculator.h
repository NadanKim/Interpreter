#pragma once
#include <iostream>

#pragma region ��ū ����
enum class TokenKind : char
{
    LeftParenthesis = '(', RightParenthesis = ')',
    Plus = '+', Minus = '-', Multiply = '*', Divide = '/',
    Assign = '=',

    Print = 1,

    VariableName, Int,

    EndOfToken,
    Others,
};

struct Token
{
    Token()
        :tokenKind(TokenKind::Others), intValue(0) {}
    Token(TokenKind tokenKind, int intValue = 0)
        :tokenKind(tokenKind), intValue(intValue) {}

    TokenKind tokenKind;
    int intValue;
};
#pragma endregion

#pragma region ���� ó��
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


#pragma region ��ū ó��
char* current;
int ch{ ' ' };

int NextCharacter()
{
	if (*current == '\0')
	{
		return '\0';
	}

	return *current++;
}

Token NextToken()
{
	// ���� ��ŵ
	while (isspace(ch))
	{
		ch = NextCharacter();
	};

	if (isdigit(ch))
	{
		int num{ 0 };
		do 
		{
			num = num * 10 + (ch - '0');
			ch = NextCharacter();
		} while (isdigit(ch));
		return Token(TokenKind::Int, num);
	}
	
	if (islower(ch))
	{
		int num{ ch - 'a' };
		ch = NextCharacter();
		return Token(TokenKind::VariableName, num);
	}

	TokenKind tokenKind{ TokenKind::Others };

	switch (ch)
	{
	case '(':
		tokenKind = TokenKind::LeftParenthesis;
		break;
	case ')':
		tokenKind = TokenKind::RightParenthesis;
		break;
	case '+':
		tokenKind = TokenKind::Plus;
		break;
	case '-':
		tokenKind = TokenKind::Minus;
		break;
	case '*':
		tokenKind = TokenKind::Multiply;
		break;
	case '/':
		tokenKind = TokenKind::Divide;
		break;
	case '=':
		tokenKind = TokenKind::Assign;
		break;
	case '?':
		tokenKind = TokenKind::Print;
		break;
	case '\0':
		tokenKind = TokenKind::EndOfToken;
		break;
	}

	ch = NextCharacter();

	return Token(tokenKind);
}
#pragma endregion