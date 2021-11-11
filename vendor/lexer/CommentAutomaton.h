#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton {
private:
    void S1(const std::string &input);
    void S2(const std::string &input); /* FINAL STATE */
    void S3(const std::string &input);
    void S4(const std::string &input); /* FINAL STATE */
public:
	CommentAutomaton() : Automaton(TokenType::COMMENT) {}
    ~CommentAutomaton() override = default;

    void S0(const std::string &input) override;
};

#endif /* COMMENTAUTOMATON_H */