#include "IdAutomaton.h"
#include <cctype>

void IdAutomaton::S0(const std::string &input) {
    // 1st char must be letter
    if(std::isalpha(input[index])){
        inputRead++;
        index++;
        S1(input);
    }else{
        Serr();
    }
}
void IdAutomaton::S1(const std::string &input) { /* FINAL STATE */
    // keep going till you find a space
    if(std::isalnum(input[index])){
        inputRead++;
        index++;
        S1(input); // should I do this recursion or just do a while loop?
    }
}
