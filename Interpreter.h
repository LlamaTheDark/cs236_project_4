#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "vendor/parser/DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
    Database db;
    DatalogProgram *dp;
public:
    Interpreter(DatalogProgram *dp);

    /*
    This will interpret all the queries given by the datalog program. It just
    runs evaluatePredicate(Predicate p) for each query.
    */
    void evaluateQueries();
    Relation *evaluatePredicate(Predicate *p);

    
};

#endif /* INTERPRETER_H */