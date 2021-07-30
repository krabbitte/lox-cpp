#ifndef LOX_TOKEN_H
#define LOX_TOKEN_H

#include <any>
#include "TokenType.h"

class Token {
public:
    TokenType type;
    std::string lexeme;

    //sucks
    std::any literal;

    int line;

        Token(TokenType type, std::string lexeme, std::any literal, int line) {
            this->type = type;
            this->lexeme = lexeme;
            this->literal = literal;
            this->line = line;
        }
        std::string toString() {
            return type + " " + lexeme = "some bull shit literal";
        }
};

#endif //LOX_TOKEN_H
