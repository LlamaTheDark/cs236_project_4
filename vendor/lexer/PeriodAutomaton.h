#ifndef PERIODAUTOMATON_H
#define PERIODAUTOMATON_H

#include "Automaton.h"

class PeriodAutomaton : public Automaton {
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}
    ~PeriodAutomaton() override = default;

    void S0(const std::string& input) override; /* FINAL STATE */
private:

};



#endif /* PERIODAUTOMATON_H */