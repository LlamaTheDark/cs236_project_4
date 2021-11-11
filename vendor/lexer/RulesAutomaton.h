#ifndef RULESAUTOMATON_H
#define RULESAUTOMATON_H

#include "Automaton.h"

class RulesAutomaton : public Automaton {
private:
    void S1(const std::string &input);
    void S2(const std::string &input);
    void S3(const std::string &input);
    void S4(const std::string &input); /* FINAL STATE */
    
public:
	RulesAutomaton() : Automaton(TokenType::RULES) {}
    ~RulesAutomaton() override = default;

    void S0(const std::string &input) override;
};

#endif /* RULESAUTOMATON_H */