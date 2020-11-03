#pragma once
#include <string>

using std::string;

enum class TokenKind : char
{
    LeftParenthesis = '(', RightParenthesis = ')',
    Plus = '+', Minus = '-', Multiply = '*', Divide = '/',

    Assign = 1, Comma, DoubleQuotes,
    Equal, NotEqual, Less, LessEqual, Grater, GraterEqual,
    If, Else, End, Print, Identifier, Int, String, Letter, Digit,
    EndOfToken, Others,
    MAX = CHAR_MAX
};

struct Token
{
    Token()
        :tokenKind(TokenKind::Others), text(""), intValue(0) {}
    Token(TokenKind tokenKind, const string& text, int intValue)
        :tokenKind(tokenKind), text(text), intValue(intValue) {}

    TokenKind tokenKind;
    string text;
    int intValue;
};