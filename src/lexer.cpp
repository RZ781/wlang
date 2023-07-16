#include <iostream>
#include <fstream>
#include "lexer.hpp"

Lexer::Lexer(std::string name) {
        f = std::ifstream(name);
        peek_token = lex();
}

bool Lexer::more(void) {
        return f.peek() != EOF;
}

Token Lexer::peek(void) {
        return peek_token;
}

Token Lexer::next(void) {
        Token ret = peek_token;
        peek_token = lex();
        return ret;
}

Token Lexer::eat(token_type type) {
        Token token = next();
        if (token.type != type)
                std::cerr << "expected " << type << " got " << token.type << std::endl;
        return token;
}

Token Lexer::eat(Token token) {
        Token t = next();
        if (t.type != token.type || t.data != token.data)
                std::cerr << "expected " << token.type << " " << token.data << std::endl;
        return token;
}

Token Lexer::lex(void) {
        while (isspace(f.peek()))
                f.get();
        int c = f.get();
        std::string data;
        token_type type;
        if (isalpha(c) || c == '_') { // id
                type = Id;
                data.push_back(c);
                while (isalnum(f.peek()) || f.peek() == '_')
                        data.push_back(f.get());
        } else if (isdigit(c)) { // int
                type = Int;
                data.push_back(c);
                while (isdigit(f.peek()) || f.peek() == '_')
                        if (isdigit(f.peek()))
                                data.push_back(f.get());
                if (f.peek() == '.') {
                        type = Float;
                        data.push_back(f.get());
                        while (isdigit(f.peek()) || f.peek() == '_')
                                if (isdigit(f.peek()))
                                        data.push_back(f.get());
                }
        } else if (c == '\'' || c == '"') { // string
                type = Str;
                while (f.peek() != c) {
                        char d = f.get();
                        if (d != '\\')
                                data.push_back(d);
                        else { // escape sequence
                                d = f.get();
                                switch (d) {
                                        case 'n':
                                                data.push_back('\n');
                                                break;
                                        case '\\':
                                                data.push_back('\\');
                                                break;
                                        default:
                                                data.push_back(d);
                                }
                        }
                }
                f.get(); // get last quote
        } else { // symbol
                type = Symbol;
                if (c == '/' && f.peek() == '/') { // single line comment
                        while (f.peek() != '\n')
                                f.get();
                        f.get();
                        return lex();
                } else if (c == '/' && f.peek() == '*') { // multiline comment
                        f.get(); // get first *
                        while (1) {
                                c = f.get();
                                if (c == '*' && f.peek() == '/')
                                        break;
                        }
                        f.get(); // get last slash
                        return lex();
                }
                data.push_back(c);
        }
        return Token {type, data};
}
