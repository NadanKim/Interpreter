#pragma once
#include <iostream>

void Factor();
void Expression();
void Term();
void AndExpression();
void EqualsExpression();
void RelationExpression();
void AddExpression();
void MultiplyExpression();

#pragma region 토큰 설정
enum class TokenKind : char
{
	LeftParenthesis = '(', RightParenthesis = ')',
	Plus = '+', Minus = '-', Multiply = '*', Divide = '/', Modular = '%',
	Assign = '=', Not = '!',

	Print = 1,

	VariableName, Int,

	Equal, NotEqual, Less, LessEqual, Grater, GraterEqual,
	And, Or,

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


#pragma region 토큰 처리
Token token;
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
	// 공백 스킵
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
	case '!':
		tokenKind = TokenKind::Not;
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

void CheckToken(TokenKind tokenKind)
{
	if (token.tokenKind != tokenKind)
	{
		std::cout << "에러 발생!\n";
		exit(1);
	}
}
#pragma endregion

#pragma region 실행 처리
int varArr[26];

// 계산 처리
void Operate(TokenKind op)
{
	int num2{ Pop() }, num1{ Pop() };

	switch (op)
	{
	case TokenKind::Plus:
		Push(num1 + num2);
		break;
	case TokenKind::Minus:
		Push(num1 - num2);
		break;
	case TokenKind::Multiply:
		Push(num1 * num2);
		break;
	case TokenKind::Divide:
		if (num2 == 0)
		{
			std::cout << "0으로 나눌 수 없습니다.\n";
			exit(1);
		}
		Push(num1 / num2);
		break;
	case TokenKind::Modular:
		if (num2 == 0)
		{
			std::cout << "0으로 나눌 수 없습니다.\n";
			exit(1);
		}
		Push(num1 % num2);
		break;
	}
}

// And 처리
void AndExpression()
{
	EqualsExpression();

	TokenKind op;
	while (token.tokenKind == TokenKind::And)
	{
		op = token.tokenKind;
		token = NextToken();
		EqualsExpression();
		Operate(op);
	}
}

// Equals 처리
void EqualsExpression()
{
	RelationExpression();

	TokenKind op;
	while (token.tokenKind == TokenKind::Equal
		|| token.tokenKind == TokenKind::NotEqual)
	{
		op = token.tokenKind;
		token = NextToken();
		RelationExpression();
		Operate(op);
	}
}

// Relation 처리
void RelationExpression()
{
	AddExpression();

	TokenKind op;
	while (token.tokenKind == TokenKind::Less
		|| token.tokenKind == TokenKind::LessEqual
		|| token.tokenKind == TokenKind::Grater
		|| token.tokenKind == TokenKind::GraterEqual)
	{
		op = token.tokenKind;
		token = NextToken();
		AddExpression();
		Operate(op);
	}
}

// +, - 처리
void AddExpression()
{
	MultiplyExpression();

	TokenKind op;
	while (token.tokenKind == TokenKind::Plus
		|| token.tokenKind == TokenKind::Minus)
	{
		op = token.tokenKind;
		token = NextToken();
		MultiplyExpression();
		Operate(op);
	}
}

// *, /, % 처리
void MultiplyExpression()
{
	Factor();

	TokenKind op;
	while (token.tokenKind == TokenKind::Multiply
		|| token.tokenKind == TokenKind::Divide
		|| token.tokenKind == TokenKind::Modular)
	{
		op = token.tokenKind;
		token = NextToken();
		Factor();
		Operate(op);
	}
}

// 인자 처리
void Factor()
{
	TokenKind op;
	switch (token.tokenKind)
	{
	case TokenKind::Plus:
	case TokenKind::Minus:
	case TokenKind::Not:
		op = token.tokenKind;
		token = NextToken();
		Factor();

		if (op == TokenKind::Minus)
		{
			Push(-Pop());
		}
		else if (op == TokenKind::Not)
		{
			Push(!Pop());
		}
		break;
	case TokenKind::VariableName:
		Push(varArr[token.intValue]);
		break;
	case TokenKind::Int:
		Push(token.intValue);
		break;
	case TokenKind::LeftParenthesis:
		token = NextToken();
		Expression();
		CheckToken(TokenKind::RightParenthesis);
		break;
	default:
		std::cout << "에러 발생!\n";
		exit(1);
	}
	token = NextToken();
}

// 식 처리
void Expression()
{
	TokenKind op;

	Term();
	while (token.tokenKind == TokenKind::Plus || token.tokenKind == TokenKind::Minus)
	{
		op = token.tokenKind;
		token = NextToken();
		Term();
		Operate(op);
	}
}

// 항 처리
void Term()
{
	TokenKind op;

	Factor();
	while (token.tokenKind == TokenKind::Multiply || token.tokenKind == TokenKind::Divide)
	{
		op = token.tokenKind;
		token = NextToken();
		Factor();
		Operate(op);
	}
}

// 문 처리
void Statement()
{
	int variableNumber;

	switch (token.tokenKind)
	{
	case TokenKind::VariableName:
		variableNumber = token.intValue;
		token = NextToken();
		CheckToken(TokenKind::Assign);

		token = NextToken();
		Expression();
		varArr[variableNumber] = Pop();
		break;
	case TokenKind::Print:
		token = NextToken();
		Expression();
		CheckToken(TokenKind::EndOfToken);

		std::cout << "   " << Pop() << '\n';
		return;
	default:
		std::cout << "에러 발생!\n";
		exit(1);
	}

	CheckToken(TokenKind::EndOfToken);
}
#pragma endregion

#pragma region 입력 처리
char buffer[80];

void Input()
{
	top = 0;
	std::fill_n(buffer, 80, 0);
	std::cin.getline(buffer, 80);
	current = buffer;
	ch = NextCharacter();
}
#pragma endregion