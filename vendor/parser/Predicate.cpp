#include "Predicate.h"

#include <sstream>

Predicate::Predicate(std::string id) {
    this->id = std::move(id);
}
Predicate::~Predicate(){
    for(auto p : parameters){
        delete p;
    }
}

void Predicate::addParameter(Parameter *p){
    parameters.push_back(p);
}

std::string Predicate::toString() const {
    std::ostringstream s;
    s << id << "(";
    for (long unsigned int i = 0; i < parameters.size()-1; i++){
        s << *(parameters[i]) << ",";
    }
    s << *(parameters[parameters.size()-1]) << ")";
    return s.str();
}
std::ostream &operator<<(std::ostream &out, const Predicate &p){
    out << p.toString();
    return out;
}