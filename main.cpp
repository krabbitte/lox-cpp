#include <iostream>
#include <cstdio>
#include <fstream>
#include "lox.h"

using namespace std;

int main(int argc, char* argv[]) {

    Lox lox;

    if (argc > 2) {
        printf("Usage: jlox [script]");
        exit(64);
    } else if (argc == 2) {
        lox.runFile(argv[1]);
    } else {
        lox.runPrompt();
    }
}



