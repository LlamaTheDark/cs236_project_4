#ifndef COLONAUTOMATON_H
#define COLONAUTOMATON_H

#include "Automaton.h"

class ColonAutomaton : public Automaton {
public:
    ColonAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor
    ~ColonAutomaton() override = default;


    void S0(const std::string& input) override; /* FINAL STATE */
};

#endif // COLONAUTOMATON_H

