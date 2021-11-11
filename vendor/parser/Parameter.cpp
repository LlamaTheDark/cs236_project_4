#include "Parameter.h"

Parameter::Parameter(std::string content, bool constant): constant(constant) {
    this->content = std::move(content);
}
Parameter::~Parameter(){}

std::string Parameter::toString() const {
    return content;
}
std::ostream &operator<<(std::ostream &out, const Parameter &p){
    out << p.toString();
    return out;
}