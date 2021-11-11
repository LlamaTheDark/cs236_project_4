#include "Rule.h"

#include <sstream>

Rule::Rule(Predicate *headPredicate): headPredicate(headPredicate) {}
Rule::~Rule(){
    delete headPredicate;
    for(auto p : predicateList){
        delete p;
    }
}

void Rule::addPredicate(Predicate *p){
    predicateList.push_back(p);
}

std::string Rule::toString() const {
    std::ostringstream s;
    s << *headPredicate << " :- ";
    
    for(long unsigned int i = 0; i < predicateList.size()-1; i++){
        s << *(predicateList[i]) << ",";
    }
    s << *(predicateList[predicateList.size()-1]); // full stop '.' taken care of in DatalogProgram.cpp
    return s.str();
}
std::ostream &operator<<(std::ostream &out, const Rule &r){
    out << r.toString();
    return out;
}