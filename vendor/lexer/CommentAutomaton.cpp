#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string &input) {
    // start with # -> s1
    if(input[index] == '#'){
        inputRead++;
        index++;
        S1(input);
    }else{
        Serr();
    }
}
void CommentAutomaton::S1(const std::string &input) {
    // check for block comment -> s3
    // otherwise -> s2
    if(input[index] == '|'){
        inputRead++;
        index++;
        S3(input);
    }else{
        inputRead++;
        index++;
        S2(input);
    }
}
void CommentAutomaton::S2(const std::string &input) { /* FINAL STATE */
    // keep adding until you hit EOF (i.e. index > input.size()) or \n
    if(index < input.size() && input[index] != '\n'){
        inputRead++;
        index++;
        S2(input);
    }
}
void CommentAutomaton::S3(const std::string &input) {
    // keep adding until you hit '|' -> s4
    if(index >= input.size()){
        type = TokenType::UNDEFINED;
    }else if(input[index] == '|'){
        inputRead++;
        index++;
        S4(input);
    }else if(input[index] == '\n'){
        linesRead++;
        inputRead++;
        index++;
        S3(input);
    }else{
        inputRead++;
        index++;
        S3(input);
    }
}
void CommentAutomaton::S4(const std::string &input) { /* FINAL STATE */
    // test for # (end of block comment) -> complete state
    // else -> s3
    if(index >= input.size()) {
        type = TokenType::UNDEFINED;
    }else if(input[index] == '#'){
        inputRead++;
    }else{
//        inputRead++;
//        index++;
        S3(input);
    }
}
