#include "Interpreter.h"
#include "Tuple.h"
#include "vendor/utils/FileHelper.h"
#include "vendor/parser/Parameter.h"

#include <vector>
#include <sstream>
#include <set>
#include <unordered_map>

#define DEVMODE
void submit(std::string &submission){
#ifdef DEVMODE
    if(!FileHelper::write("out/tests/output.txt", submission))
        std::cout << "Failed to write file" << std::endl;
#else
    std::cout << submission;
#endif
}

Interpreter::Interpreter(DatalogProgram *dp): dp(dp){
    db = Database();

    // evaluate schemes
    for(auto scheme : *(dp->getSchemes())){
        Header *header = new Header();

        for(auto parameter : *(scheme->getParameters())){
            header->addAttribute(*parameter->toString());
        }

        std::string *name = scheme->getId();
        db.addRelation(*name, new Relation(*name, header));
    }
    // evalutate facts
    for(auto fact : *(dp->getFacts())){
        Tuple *instance = new Tuple();

        for(auto parameter : *(fact->getParameters())){
            instance->addValue(*parameter->toString());
        }

        db.getRelation( *fact->getId() )->addInstance(instance);
    }

}

void Interpreter::interpretProgram(){
    std::cout << "Rule Evaluation" << std::endl;
    evaluateRules();
    
    std::cout << "Query Evaluation" << std::endl;
    evaluateQueries();
}

void Interpreter::evaluateRules(){
    int n = 0;

    while(/* new tuples added */1){
        for(auto rule : *dp->getRules()){
            std::cout << *rule << std::endl;
            Relation *r = evaluateRule(rule);
            // union r with relation of same name
            db.getRelation(*rule->getHeadId())->performUnion(r);
        }
        
        n++;
    }

    std::cout << "\nSchemes populated after " << n << "passes through the Rules." << std::endl;
    
}
Relation *Interpreter::evaluateRule(Rule *rule){
    Relation *result;
    Relation *tmp;
    {// first, evaluate all predicates held in the rule
        std::vector<Relation*> intermediaries;
        for(auto predicate : *rule){
            intermediaries.push_back(evaluatePredicate(predicate));
        }

        // join all evaluated intermediary relations in order
        result = intermediaries[0];
        for(unsigned int i = 1; i < intermediaries.size(); i++){
            // TODO: implement the Relation::join()
            tmp = result->join(intermediaries[i]);
            *result = *tmp;
            delete tmp;
        }
    }

    // project all columns that appear in the head predicate of the rule
    //      first find indices of columns that match the head predicate variable names
    {
        std::vector<int> indices;
        int count;

        for(auto parameter : *rule->getHeadParameters()){
            count = 0;
            while(*parameter->toString() != result->getAttribute(count)) {
                count++;
            }
            indices.push_back(count);
        }

        tmp = result->project(indices);
        *result = *tmp;
        delete tmp;
    }

    // rename the columns of the projected relation to match the attribute names
    // of the relation within the database with the same name.
    Relation *match = db.getRelation( *rule->getHeadId() );
    {
        std::unordered_map<std::string_view, int> attributes;
        for(int i = 0; i < match->headerLength(); i++){
            attributes[match->getAttribute(i)] = i;
        }

        tmp = result->rename(attributes);
        *result = *tmp;
        delete tmp;
    }
    
    // union the renamed relation with the relation of the same name in the database
    // {
    //     match->performUnion(result);
    // }
    return result;
}

void Interpreter::evaluateQueries(){
    // create output stream
    std::ostringstream oss;

    for(auto query : *(dp->getQueries())){
        Relation *r = evaluatePredicate(query);
        oss << *query << "?";

        // if query is empty, that means we didn't find any results for the query
        if(r->isEmpty()){
            oss << " No" << std::endl;
        }else{
            // otherwise, we know we've found some and we can print them out.
            oss << " Yes(" << r->instanceCount() << ")" << std::endl;
            oss << *r;
        }
    }
    // oss << std::endl;

    std::string result = oss.str();
    submit(result);
}

Relation *Interpreter::evaluatePredicate(Predicate *predicate){
    Relation *tmp;
    Parameter *p;
    std::string pString;
    Relation *result = new Relation();

    /*
    variables is a map that links each non-constant (variable) parameter we've seen to the index
    that it first appeared.
    */
    std::unordered_map<std::string_view, int> variables;

    // get relevant relation
    *result = *db.getRelation( *predicate->getId() );

    std::vector<Parameter*> queryParameters = *(predicate->getParameters());

    for(unsigned int i = 0; i < queryParameters.size(); i++){
        p = queryParameters.at(i);
        pString = *p->toString();
        if(p->isConstant()){
            // selects all instances (rows) that have the value queryParameters[i] in column i
            tmp = result->select(i, *p->toString());
            *result = *tmp;
            delete tmp;
        }else{
            // search the map for anything with the same name
            // if we have the same name, we want to select for those two columns
            // if we can't find the same name, then we want to add the variable
            //    to the map.

            auto it = variables.begin();
            while(
                it != variables.end()
                && it->first != *p->toString()
            ){
                it++;
            }

            // at this point, i should point to either the end of the map or the variable with the same name
            // if it got to the end of the map, we want to select
            // otherwise, we should add the variable to the map.

            if(it == variables.end()){
                variables[*p->toString()] = i;
            }else{
                tmp = result->select(i, it->second);
                *result = *tmp;
                delete tmp;
            }
        }
    }
    // build set containing indices of variables (if any)
    std::set<int> indices;

    for(auto var : variables){
        indices.insert(var.second);
    }

    // rename relevant attributes to variables found in query
    tmp = result->rename(variables);
    *result = *tmp;
    delete tmp;

    // project relevant columns (those with variables)
    tmp = result->project(indices);
    *result = *tmp;
    delete tmp;

    return result;
}