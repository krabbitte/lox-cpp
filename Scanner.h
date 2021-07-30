#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

#include <any>
#include <map>
#include <list>
#include "Token.h"
#include "TokenType.h"
#include "lox.h"

class Scanner {

    private:
        std::map<std::string, TokenType> keywords;
        std::string source;
        std::list<Token> tokens = {};
        int start = 0;
        int current = 0;
        int line  = 1;
        bool isAtEnd();
        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, std::any literal);
        bool match(char expected);
        char peek();
        char peekNext();
        void string();
        void number();
        void identifier();

    public:
        std::list<Token> scanTokens();
        void scanToken();

        Scanner(std::string source) {
            this->source = source;

            keywords["and"] = AND;
            keywords["class"] = CLASS;
            keywords["else"] = ELSE;
            keywords["false"] = FALSE;
            keywords["for"] = FOR;
            keywords["fun"] = FUN;
            keywords["if"] = IF;
            keywords["nil"] = NIL;
            keywords["or"] = OR;
            keywords["print"] = PRINT;
            keywords["return"] = RETURN;
            keywords["super"] = SUPER;
            keywords["this"] = THIS;
            keywords["true"] = TRUE;
            keywords["var"] = VAR;
            keywords["while"] = WHILE;
        }
};

std::list<Token> Scanner::scanTokens() {

    while(!isAtEnd()) {
        start = current;
        scanToken();
    }

    return tokens;
}

void Scanner::scanToken() {

    char c = advance();

    switch(c) {
        //Single Character tokens
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break;

        //Multi-character tokens
        //EQUAL
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;

        case '/':
            if(match('/')) {
                while(peek() != '\n' && !isAtEnd()){
                    advance();
                }
            } else {
                addToken(SLASH);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
            //ignore whitespace
            break;
        case '\n':
            line++;
            break;

        case '"': string(); break;


        //find out how to call form the "Lox" instance in main from here and fix this
        default:
            if(isdigit(c)) {
                number();
            } else if (isalpha(c)){
                identifier();
            } else {
                std::cerr << "fuck"; exit(420);
            }
    }
}

void Scanner::identifier() {
    while(isalnum(peek())) advance();

    std::string text = source.substr(start, current-start);
    TokenType type = keywords[text];
    if (type == NULL) type = IDENTIFIER;
    addToken(type);
}

void Scanner::number() {
    while(isdigit(peek())) advance();

    //Look for fractional part
    if(peek() == '.' && isdigit(peekNext())) {
        //consume the '.'
        advance();

        while(isdigit(peek())) advance();
    }

    addToken(NUMBER, std::stod(source.substr(start, current-start)));
}

void Scanner::string() {
    while(peek() != '"' && !isAtEnd()) {
        if(peek() == '\n') line++;
        advance();
    }

    if(isAtEnd()) {
        //you gotta fix this bit too
        std::cerr << "string messed up";
        exit(420);
    }

    //The closing '"'
    advance();

    //trim the surrounding quotes
    std::string value = source.substr(start + 1, current - 1);
    addToken(STRING, &value);
}

bool Scanner::match(char expected) {
    if(isAtEnd()) return false;
    if(source[current] != expected) return false;

    current++;
    return true;
}

char Scanner::peek() {
    if(isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if(current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    return source[current++];
}

void Scanner::addToken(TokenType type) {
    addToken(type, NULL);
}

void Scanner::addToken(TokenType type, std::any literal) {
    std::string text = source.substr(start, current-start);

    Scanner::tokens.push_back(*(new Token(type, text, literal, line)));
}

#endif //LOX_SCANNER_H
