#pragma once
#include <iostream>

#pragma region 토큰 설정
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