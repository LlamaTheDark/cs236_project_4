#include "MultiplyAutomaton.h"

void MultiplyAutomaton::S0(const std::string &input) { /* FINAL STATE */
    if(input[index] == '*'){
        inputRead = 1;
    }else{
        Serr();
    }
}
