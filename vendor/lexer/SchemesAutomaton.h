#ifndef SCHEMESAUTOMATON_H
#define SCHEMESAUTOMATON_H

#include "Automaton.h"

class SchemesAutomaton : public Automaton {
private:
    void S1(const std::string &input);
    void S2(const std::string &input);
    void S3(const std::string &input);
    void S4(const std::string &input);
    void S5(const std::string &input);
    void S6(const std::string &input); /* FINAL STATE */

public:
	SchemesAutomaton() : Automaton(TokenType::SCHEMES) {}
    ~SchemesAutomaton() override = default;

	void S0(const std::string &input) override;
};

#endif /* SCHEMESAUTOMATON_H */