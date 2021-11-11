#include "AddAutomaton.h"

void AddAutomaton::S0(const std::string &input) { /* FINAL STATE */
    if(input[index] == '+'){
        inputRead = 1;
    }else{
        Serr();
    }
}
