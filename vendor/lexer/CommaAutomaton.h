#ifndef COMMAAUTOMATON_H
#define COMMAAUTOMATON_H

#include "Automaton.h"

class CommaAutomaton : public Automaton {
public:
	CommaAutomaton() : Automaton(TokenType::COMMA) {}
    ~CommaAutomaton() override = default;

	void S0(const std::string &input) override; /* FINAL STATE */
};

#endif /* COMMAAUTOMATON_H */