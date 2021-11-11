#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <utility>

#include "Token.h"


class Automaton {
protected:
    int inputRead = 0;
    unsigned int index = 0;
    int linesRead = 0;
    TokenType type;

    // Indicate the input was rejected
    void Serr() {
        linesRead = 0;
        inputRead = 0;
    }
public:
    // Default constructor -- since we have a constructor that takes a parameter,
    //   the compiler will autogenerate a default constructor if not explicit.
    Automaton() : Automaton(TokenType::UNDEFINED) {}

    explicit Automaton(TokenType type) { this->type = type; }
    virtual ~Automaton() = default;

    // Every subclass must define this method
    virtual void S0(const std::string& input) = 0;

    // Start the automaton and return the number of characters read
    //   read == 0 indicates the input was rejected
    //   read  > 0 indicates the input was accepted
    int Start(const std::string& input) {
        linesRead = 0;
        inputRead = 0;
        index = 0;
        S0(input);
        return inputRead;
    }


    // create a token of the given type
    Token* CreateToken(std::string input, int lineNumber) {
        return new Token(type, std::move(input), lineNumber);
    }

    // accessor for the variable linesRead
    int NewLinesRead() const { return this->linesRead; }
};

#endif // AUTOMATON_H
