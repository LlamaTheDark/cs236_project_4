#ifndef MULTIPLYAUTOMATON_H
#define MULTIPLYAUTOMATON_H

#include "Automaton.h"

class MultiplyAutomaton : public Automaton {
public:
	MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}
    ~MultiplyAutomaton() override = default;

	void S0(const std::string &input) override; /* FINAL STATE */
};

#endif /* MULTIPLYAUTOMATON_H */