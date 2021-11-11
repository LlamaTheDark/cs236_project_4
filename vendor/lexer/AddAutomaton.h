#ifndef ADDAUTOMATON_H
#define ADDAUTOMATON_H

#include "Automaton.h"

class AddAutomaton : public Automaton {
public:
	AddAutomaton() : Automaton(TokenType::ADD) {}
	~AddAutomaton() override = default;

	void S0(const std::string &input) override; /* FINAL STATE */
};

#endif /* ADDAUTOMATON_H */