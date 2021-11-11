#ifndef RULE_H
#define RULE_H

#include "Predicate.h"
#include "Parameter.h"

#include <vector>
#include <string>
#include <iostream>


class Rule {
private:
    Predicate *headPredicate;
    std::vector<Predicate*> predicateList;
public:
    Rule(Predicate *headPredicate);
    ~Rule();

    void addHeadParameter(Parameter *p);
    void addPredicate(Predicate *p);

    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &out, const Rule &r);
};

#endif /* RULE_H */