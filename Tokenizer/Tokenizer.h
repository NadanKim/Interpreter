#pragma once
#include <iostream>
#include <string>

using std::string;

#pragma region 토큰 설정
enum class TokenKind : char
{
    LeftParenthesis = '(', RightParenthesis = ')',
    Plus = '+', Minus = '-', Multiply = '*', Divide = '/',

    Assign = 1, Comma, DoubleQuotes,
    Equal, NotEqual, Less, LessEqual, Grater, GraterEqual,
    If, Else, End, Print, Identifier, Int, String, Letter, Digit,
    EndOfList, Others,
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
#pragma endregion

#pragma region 문자 종류표
TokenKind charType[256];

void InitializeCharTypeTable()
{
    std::fill_n(charType, 256, TokenKind::Others);

    for (int i = '0'; i <= '9'; charType[i++] = TokenKind::Digit);
    for (int i = 'A'; i <= 'Z'; charType[i++] = TokenKind::Letter);
    for (int i = 'a'; i <= 'z'; charType[i++] = TokenKind::Letter);

    charType['_'] = TokenKind::Letter;

    charType['('] = TokenKind::LeftParenthesis;
    charType[')'] = TokenKind::LeftParenthesis;

    charType['<'] = TokenKind::Less;
    charType['<'] = TokenKind::Grater;

    charType['+'] = TokenKind::Plus;
    charType['-'] = TokenKind::Minus;
    charType['*'] = TokenKind::Multiply;
    charType['/'] = TokenKind::Divide;
    charType['='] = TokenKind::Assign;

    charType[','] = TokenKind::Comma;

    charType['\"'] = TokenKind::DoubleQuotes;
}
#pragma endregion

#pragma region 식별자표
struct Identifier
{
    const char* keyWord;
    TokenKind type;
};

Identifier identifier[] = {
    {"if", TokenKind::If},
    {"else", TokenKind::Else},
    {"end", TokenKind::End},

    {"print", TokenKind::Print},

    {"(", TokenKind::LeftParenthesis},
    {")", TokenKind::RightParenthesis},

    {"==", TokenKind::Equal},
    {"!=", TokenKind::NotEqual},

    {"<", TokenKind::Less},
    {">", TokenKind::Grater},
    {"<=", TokenKind::LessEqual},
    {">=", TokenKind::GraterEqual},

    {"+", TokenKind::Plus},
    {"-", TokenKind::Minus},
    {"*", TokenKind::Multiply},
    {"/", TokenKind::Divide},
    {"=", TokenKind::Assign},

    {"", TokenKind::EndOfList}
};
#pragma endregion