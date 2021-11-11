#ifndef RIGHTPARENAUTOMATON_H
#define RIGHTPARENAUTOMATON_H

#include "Automaton.h"

class RightParenAutomaton : public Automaton {
public:
	RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}
    ~RightParenAutomaton() override = default;

	void S0(const std::string &input) override; /* FINAL STATE */
};

#endif /* RIGHTPARENAUTOMATON_H */