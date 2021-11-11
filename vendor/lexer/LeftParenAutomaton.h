#ifndef LEFTPARENAUTOMATON_H
#define LEFTPARENAUTOMATON_H

#include "Automaton.h"

class LeftParenAutomaton : public Automaton {
public:
	LeftParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}
    ~LeftParenAutomaton() override = default;

	void S0(const std::string &input) override; /* FINAL STATE */
};

#endif /* LEFTPARENAUTOMATON_H */