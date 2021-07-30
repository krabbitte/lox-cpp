#ifndef LOX_LOX_H
#define LOX_LOX_H

#include <list>
#include "Scanner.h"
#include "Token.h"
#include "TokenType.h"

class Lox {
public:
    bool runFile(std::string path);
    bool runPrompt();
    bool run(std::string source);
    void error(int line, std::string message);
    void report(int line, std::string where, std::string message);

    bool hadError;
};

bool Lox::runFile(std::string path) {

    bool success = true;

    //Open file
    unsigned char* bytes;
    std::ifstream myScript(path, std::ios::binary);

    // Determine the size of the array
    int sSize, begin, end;
    begin = myScript.tellg();
    myScript.seekg(0, std::ios::end);
    end = myScript.tellg();
    myScript.seekg(0 , std::ios::beg);
    sSize = end - begin;

    bytes = new unsigned char [sSize];

    //Copy contents of file into array
    if (myScript.is_open()) {
        for(int i = 0; i < sSize; i++) {
            bytes[i] = myScript.get();
        }
    } else {
        success = false;
    }

    //Unsure if necessary yet, may need to be revised. Just following the book.
    std::string source = "";
    for(int i = 0; i < sSize; i++) {
        source += bytes[i];
    }

    run(source);

    if (hadError) exit(65);

    return success;
}

bool Lox::runPrompt() {
    int success = true;
    std::string line;

    //Prompt Loop
    for(;;) {
        std::cout << "> ";
        std::cin >> line;

        if (line == "") break;

        run(line);
    }

    return success;
}

bool Lox::run(std::string source) {
    bool success = true;

    Scanner scanner(source);

    std::list<Token> tokens = scanner.scanTokens();

    for (Token token: tokens) {
        std::cout << token.lexeme << std::endl;
    }

    return success;
}

void Lox::error(int line, std::string message) {
    report(line, "", message);
}

void Lox::report(int line, std::string where, std::string message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message;
}

#endif //LOX_LOX_H
