#pragma once
#include <iostream>
#include <fstream>
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
    EndOfToken, Others,
    MAX = CHAR_MAX
};

struct Token
{
    Token()
        :tokenKind(TokenKind::Others), text(""), intValue(0) {}
    Token(TokenKind tokenKind, const string& text, int intValue = 0)
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

#pragma region 키워드표
struct Keyword
{
    const char* str;
    TokenKind type;
};

Keyword keywordList[] = {
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
};

TokenKind GetKind(const string& str)
{
    for (const Keyword& keyword : keywordList)
    {
        if (str == keyword.str)
        {
            return keyword.type;
        }
    }

    if (charType[str[0]] == TokenKind::Letter)
    {
        return TokenKind::Identifier;
    }

    return TokenKind::Others;
}
#pragma endregion

#pragma region 파일 처리
std::ifstream ifs;

bool OpenFile(const char* path)
{
    ifs.open(path);
    
    if (ifs.is_open())
    {
        return true;
    }

    return false;
}
#pragma endregion


#pragma region 토큰 처리
string emptyString{ "" };
int ch{ ' ' };

int NextCharacter()
{
    if (ifs.is_open())
    {
        if (ifs.eof())
        {
            ifs.close();
        }
        else
        {
            return ifs.get();
        }
    }

    return EOF;
}

bool IsSize2Operator(const int ch1, const int ch2)
{
    static string size2Operator{ ">= <= == !=" };

    if (ch1 == '\0' || ch2 == '\0')
    {
        return false;
    }
    
    string op(sizeof(ch1), ch1);
    op.append(sizeof(ch2), ch2);

    return size2Operator.find(op) != string::npos;
}

Token NextToken()
{
    if (ch == EOF)
    {
        return Token(TokenKind::EndOfToken, emptyString);
    }

    // 공백 스킵
    while (isspace(ch))
    { 
        ch = NextCharacter();
    };

    string str{ emptyString };
    int num{ 0 };

    switch (charType[ch])
    {
    case TokenKind::Digit:
        do
        {
            num = num * 10 + (ch - '0');
            ch = NextCharacter();
        } while (charType[ch] == TokenKind::Digit);
        return Token(TokenKind::Int, str, num);
    case TokenKind::DoubleQuotes:
        ch = NextCharacter();
        while (charType[ch] != TokenKind::DoubleQuotes)
        {
            str.append(sizeof(ch), ch);
            ch = NextCharacter();
            if (ch == EOF)
            {
                std::cout << "\"의 짝이 맞지 않습니다.";
                exit(1);
            }
        }
        ch = NextCharacter();
        return Token(TokenKind::String, str);
    case TokenKind::Letter:
        do
        {
            str.append(sizeof(ch), ch);
            ch = NextCharacter();
        } while (charType[ch] == TokenKind::Letter);
        break;
    default:
        str.append(sizeof(ch), ch);
        ch = NextCharacter();
        if (IsSize2Operator(*str.c_str(), ch))
        {
            str.append(sizeof(ch), ch);
            ch = NextCharacter();
        }
        break;
    }

    TokenKind tokenKind{ GetKind(str) };
    
    if (tokenKind == TokenKind::Others)
    {
        std::cout << "지원하지 않는 문자입니다.";
        exit(1);
    }

    return Token(tokenKind, str);
}
#pragma endregion