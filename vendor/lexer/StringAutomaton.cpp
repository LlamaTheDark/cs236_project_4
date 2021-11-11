#include <iostream>
#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string &input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    } else {
        Serr();
    }
}
void StringAutomaton::S1(const std::string &input) { /* FINAL STATE */
    // add every character until we see a single apostrophe.
    // Check for double apostrophes (those mean single apostrophes when printed)
    // but do NOT convert double apostrophes.

    // if we have reached the end of the file without finding an end,
    // then we set it to undefined and load it all as a token.
    if (index >= input.size()) {
        type = TokenType::UNDEFINED;
    }else{
        if (input[index] == '\'') {
            inputRead++;
            index++;
            S2(input);
        }else if(input[index] == '\n'){
            linesRead++;
            inputRead++;
            index++;
            S1(input);
        } else {
            inputRead++;
            index++;
            S1(input);
        }
    }
}
void StringAutomaton::S2(const std::string &input) { /* FINAL STATE */
    if(input[index]== '\''){ // double apostrophe
        inputRead++;
        index++;
        S1(input);
    }// otherwise we've hit the end
}

