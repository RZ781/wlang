#pragma once
#include <fstream>

enum token_type {
        Id,
        Int,
        Float,
        Str,
        Symbol
};

struct Token {
        token_type type;
        std::string data;
};

class Lexer {
private:
        std::ifstream f;
        Token peek_token;
        Token lex(void);
public:
        Lexer(std::string name);
        bool more(void);
        Token peek(void);
        Token next(void);
        Token eat(token_type type);
        Token eat(Token token);
};
