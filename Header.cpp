#include "Header.h"

Header::Header(){}

void Header::addAttribute(std::string_view attribute){
    attributes.push_back(attribute);
}
void Header::setAttribute(std::string_view attribute, int index){
    attributes.at(index) = attribute;
}

std::string_view Header::getAttribute(int index){
    return attributes.at(index);
}

unsigned int Header::getLength(){
    return attributes.size();
}