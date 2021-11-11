#ifndef FACTSAUTOMATON_H
#define FACTSAUTOMATON_H

#include "Automaton.h"

class FactsAutomaton : public Automaton {
private:
    void S1(const std::string &input);
    void S2(const std::string &input);
    void S3(const std::string &input);
    void S4(const std::string &input); /* FINAL STATE */
public:
	FactsAutomaton() : Automaton(TokenType::FACTS) {}
    ~FactsAutomaton() override = default;

    void S0(const std::string &input) override;
};

#endif /* FACTSAUTOMATON_H */