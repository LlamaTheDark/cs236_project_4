#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include "Automaton.h"

class IdAutomaton : public Automaton {
private:
    void S1(const std::string &input); /* FINAL STATE */

public:
	IdAutomaton() : Automaton(TokenType::ID) {}
    ~IdAutomaton() override = default;

    void S0(const std::string &input) override;
};

#endif /* IDAUTOMATON_H */