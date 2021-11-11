#ifndef QUERIESAUTOMATON_H
#define QUERIESAUTOMATON_H

#include "Automaton.h"

class QueriesAutomaton : public Automaton {
private:
    void S1(const std::string &input);
    void S2(const std::string &input);
    void S3(const std::string &input);
    void S4(const std::string &input);
    void S5(const std::string &input);
    void S6(const std::string &input); /* FINAL STATE */

public:
	QueriesAutomaton() : Automaton(TokenType::QUERIES) {}
    ~QueriesAutomaton() override = default;

    void S0(const std::string &input) override;
};

#endif /* QUERIESAUTOMATON_H */