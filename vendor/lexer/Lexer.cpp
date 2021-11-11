#include "Lexer.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QuestionMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "IdAutomaton.h"

#include <cctype>
#include <sstream>
#include <algorithm>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for (Automaton *automaton : automata){
        delete automaton;
    }
    for (Token *token : tokens){
        delete token;
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QuestionMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new IdAutomaton());
}

void Lexer::Run(std::string& input) {
    int maxRead; // maximum length read
    Automaton *maxAutomaton; // corresponding maximum automaton

    int lineNumber = 1; // line number we're looking at

    // remove leading whitespace
    handleWhiteSpace(input, lineNumber);

    while(!input.empty()){
        maxRead = 0;
        maxAutomaton = automata.at(0);

        // PARALLEL
        for(auto a : automata){
            int inputRead = a->Start(input);
            if(inputRead > maxRead){
                maxRead = inputRead;
                maxAutomaton = a;
            }
        }

        // MAX READ
        Token *newToken;
        if(maxRead > 0){ // if a token was recognized
            newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }else{
            maxRead = 1;
            newToken = new Token(TokenType::UNDEFINED, input.substr(0, 1), lineNumber);
            tokens.push_back(newToken);
        }

        input.erase(0, maxRead);

        // dealing with whitespace
        handleWhiteSpace(input, lineNumber);
    }
    tokens.push_back(new Token(TokenType::FILE_END, "", lineNumber));
}

void Lexer::handleWhiteSpace(std::string &input, int &lineNumber){
    int whitespace = 0;
    while(std::isspace(input[whitespace])){
        if(input[whitespace] == '\n')
            lineNumber += 1;
        whitespace++;
    }
    input.erase(0, whitespace);
}

std::vector<Token*> &Lexer::getTokens(){
    for(std::vector<Token*>::size_type i = 0; i < tokens.size(); i++){
        if(tokens.at(i)->getType() == TokenType::COMMENT){
            tokens.erase(tokens.begin()+(i--));
        }
    }
    
    return this->tokens;
}


// converts tokens to a string representation and stores it in result
std::string Lexer::toString() const{
    std::ostringstream ss;
    ss << *this;
    return ss.str();
}

std::ostream &operator<<(std::ostream &out, const Lexer &lexer){
    for(auto t : lexer.tokens){
        out << "(" << *t << ",\"" << t->getDescription() << "\"," << t->getLine() << ")" << std::endl;
    }
    out << "Total Tokens = " << lexer.tokens.size();
    return out;
}
