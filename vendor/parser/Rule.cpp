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

std::vector<Predicate*>::iterator Rule::begin(){ return predicateList.begin(); }
std::vector<Predicate*>::iterator Rule::end(){ return predicateList.end(); }

std::string Rule::toString() const {
    std::ostringstream s;
    s << *headPredicate << " :- ";
    
    for(long unsigned int i = 0; i < predicateList.size()-1; i++){
        s << *(predicateList[i]) << ",";
    }
    s << *(predicateList[predicateList.size()-1]) << ".";
    return s.str();
}
std::ostream &operator<<(std::ostream &out, const Rule &r){
    out << r.toString();
    return out;
}