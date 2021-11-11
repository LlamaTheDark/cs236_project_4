#ifndef QUESTIONMARKAUTOMATON_H
#define QUESTIONMARKAUTOMATON_H

#include "Automaton.h"

class QuestionMarkAutomaton : public Automaton {
public:
	QuestionMarkAutomaton() : Automaton(TokenType::Q_MARK) {}
    ~QuestionMarkAutomaton() override = default;

	void S0(const std::string &input) override; /* FINAL STATE */
};

#endif /* QUESTIONMARKAUTOMATON_H */