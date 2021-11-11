#include "Tuple.h"

Tuple::Tuple(){}

void Tuple::addValue(std::string_view value){
    values.push_back(value);
}
std::string_view Tuple::getValue(int index) const {
    return values.at(index);
}

unsigned int Tuple::getLength(){
    return this->values.size();
}

