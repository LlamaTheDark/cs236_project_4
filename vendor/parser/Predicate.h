#ifndef PREDICATE_H
#define PREDICATE_H

#include <vector>
#include <string>

#include "Parameter.h"

/*
Class to represent schemes, facts, and queries (they all have the same structure)
*/

class Predicate {
private:
    std::string id;
    std::vector<Parameter*> parameters;
public:
    Predicate(std::string id);
    ~Predicate();

    void addParameter(Parameter *p);


    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &out, const Predicate &p);
    
    // MUTATORS
    std::vector<Parameter*> *getParameters() { return &parameters; }
    std::string *getId() { return &id; }
};

#endif /* PREDICATE_H */