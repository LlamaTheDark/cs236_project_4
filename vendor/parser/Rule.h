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

    std::vector<Parameter*> *getHeadParameters(){ return headPredicate->getParameters(); }
    std::string *getHeadId(){ return headPredicate->getId(); }

    // range-based for loop
    std::vector<Predicate*>::iterator begin();
    std::vector<Predicate*>::iterator end();
    // ---

    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &out, const Rule &r);
};

#endif /* RULE_H */