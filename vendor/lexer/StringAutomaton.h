#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton {
private:
    void S1(const std::string &input); /* FINAL STATE */
    void S2(const std::string &input); /* FINAL STATE */

public:
	StringAutomaton() : Automaton(TokenType::STRING) {}
    ~StringAutomaton() override = default;

    void S0(const std::string &input) override;

};

#endif /* STRINGAUTOMATON_H */