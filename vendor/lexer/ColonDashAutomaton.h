#ifndef COLONDASHAUTOMATON_H
#define COLONDASHAUTOMATON_H

#include "Automaton.h"

class ColonDashAutomaton : public Automaton {
private:
    void S1(const std::string& input);

public:
    ColonDashAutomaton() : Automaton(TokenType::COLON_DASH) {}  // Call the base constructor
    ~ColonDashAutomaton() override = default;

    void S0(const std::string& input) override; /* FINAL STATE */
};

#endif // COLONDASHAUTOMATON_H

