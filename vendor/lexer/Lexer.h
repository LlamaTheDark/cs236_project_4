#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include <iostream>
#include "Automaton.h"
#include "Token.h"

class Lexer {
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    static void handleWhiteSpace(std::string &input, int &lineNumber);

    void CreateAutomata();

public:
    Lexer();
    ~Lexer();

    std::vector<Token*> &getTokens();

    void Run(std::string& input);
    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &out, const Lexer &lexer);
};

#endif // LEXER_H

