#include "DatalogProgram.h"
#include <sstream>

DatalogProgram::DatalogProgram(){}
DatalogProgram::~DatalogProgram(){
    for(auto r : rules){
        delete r;
    }
    for(auto s : schemes){
        delete s;
    }
    for(auto f : facts){
        delete f;
    }
    for(auto q : queries){
        delete q;
    }
}

void DatalogProgram::start(TokenList &input, bool showSuccessOutput) {
    index = 0;
    // recursive descent parser to check grammar
    try{
        parseDatalogProgram(input);
        if(showSuccessOutput){
            std::cout << "Success!" << std::endl;
            std::cout << *this << std::endl;
        }
    }catch(int e){
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << input.at(index)->toString(true) << std::endl
         << " which is the " << index+1 << "th token" << std::endl;
        std::cerr << "Program failed with exit code: (" << e << ")" << std::endl;
    }    
}

// ############################################################################
// PARSE FUNCTIONS
// ############################################################################

void DatalogProgram::parseDatalogProgram(TokenList &input){
    // only one production for this, so no need to do any FIRST testing
    parseTerminal(input, TokenType::SCHEMES);
    parseTerminal(input, TokenType::COLON);
    parseScheme(input);
    parseSchemeList(input);
    parseTerminal(input, TokenType::FACTS);
    parseTerminal(input, TokenType::COLON);
    parseFactList(input);
    parseTerminal(input, TokenType::RULES);
    parseTerminal(input, TokenType::COLON);
    parseRuleList(input);
    parseTerminal(input, TokenType::QUERIES);
    parseTerminal(input, TokenType::COLON);
    parseQuery(input);
    parseQueryList(input);
    parseTerminal(input, TokenType::FILE_END);
}

void DatalogProgram::parseSchemeList(TokenList &input){
    TokenType currType = input.at(index)->getType();
    if(tokenInSet(FIRST_predicate, FIRST_predicate_c, currType)){
        parseScheme(input);
        parseSchemeList(input);
    }else if(!tokenInSet(FOLLOW_schemeList, FOLLOW_schemeList_c, currType)){
        throw -2;
   }
}
void DatalogProgram::parseFactList(TokenList &input){
    TokenType currType = input.at(index)->getType();
    if(tokenInSet(FIRST_predicate, FIRST_predicate_c, currType)){
        parseFact(input);
        parseFactList(input);
    }else if(!tokenInSet(FOLLOW_factList, FOLLOW_factList_c, currType)){
        throw -3;
   }
}
void DatalogProgram::parseRuleList(TokenList &input){
    TokenType currType = input.at(index)->getType();
    if(tokenInSet(FIRST_predicate, FIRST_predicate_c, currType)){
        parseRule(input);
        parseRuleList(input);
    }else if(!tokenInSet(FOLLOW_ruleList, FOLLOW_ruleList_c, currType)){
        throw -4;
   }
}
void DatalogProgram::parseQueryList(TokenList &input){
    TokenType currType = input.at(index)->getType();
    if(tokenInSet(FIRST_predicate, FIRST_predicate_c, currType)){
        parseQuery(input);
        parseQueryList(input);
    }else if(!tokenInSet(FOLLOW_queryList, FOLLOW_queryList_c, currType)){
        throw -5;
   }
}

void DatalogProgram::parseScheme(TokenList &input){
    // if something breaks it might be this line
    /*
    For this, we add the description after it's been verified by appending
    input[index-1] beacuse a successful parse of a terminal increments
    the index.
    */
    parseTerminal(input, TokenType::ID);
    Predicate *scheme = new Predicate(input[index-1]->getDescription());

    parseTerminal(input, TokenType::LEFT_PAREN);
    parseTerminal(input, TokenType::ID);
    scheme->addParameter(new Parameter(input[index-1]->getDescription(),
                                        input[index-1]->getType() == TokenType::STRING));
    
    parseIdList(input, scheme);
    parseTerminal(input, TokenType::RIGHT_PAREN);
    schemes.push_back(scheme);
}
void DatalogProgram::parseFact(TokenList &input){
    parseTerminal(input, TokenType::ID);
    Predicate *fact = new Predicate(input[index-1]->getDescription());

    parseTerminal(input, TokenType::LEFT_PAREN);
    parseTerminal(input, TokenType::STRING);
    domain.insert(input[index-1]->getDescription());
    fact->addParameter(new Parameter(input[index-1]->getDescription(),
                                        input[index-1]->getType() == TokenType::STRING));

    parseStringList(input, fact);
    parseTerminal(input, TokenType::RIGHT_PAREN);
    parseTerminal(input, TokenType::PERIOD);

    facts.push_back(fact);
}
void DatalogProgram::parseRule(TokenList &input){
    Rule *rule;
    Predicate *headPredicate;
    parseHeadPredicate(input, headPredicate);
    rule = new Rule(headPredicate);

    parseTerminal(input, TokenType::COLON_DASH);

    Predicate *p;
    parsePredicate(input, p);
    rule->addPredicate(p);

    parsePredicateList(input, rule);
    parseTerminal(input, TokenType::PERIOD);

    rules.push_back(rule);
}
void DatalogProgram::parseQuery(TokenList &input){
    Predicate *query;
    parsePredicate(input, query);
    queries.push_back(query);

    parseTerminal(input, TokenType::Q_MARK);
}

void DatalogProgram::parseHeadPredicate(TokenList &input, Predicate *&headPredicate){
    parseTerminal(input, TokenType::ID);
    headPredicate = new Predicate(input[index-1]->getDescription());

    parseTerminal(input, TokenType::LEFT_PAREN);
    parseTerminal(input, TokenType::ID);
    headPredicate->addParameter(new Parameter(input[index-1]->getDescription(),
                                        input[index-1]->getType() == TokenType::STRING));

    parseIdList(input, headPredicate);
    parseTerminal(input, TokenType::RIGHT_PAREN);

}
void DatalogProgram::parsePredicate(TokenList &input, Predicate *&p){
    parseTerminal(input, TokenType::ID);
    p = new Predicate(input[index-1]->getDescription());

    parseTerminal(input, TokenType::LEFT_PAREN);
    parseParameter(input, p);
    parseParameterList(input, p);
    parseTerminal(input, TokenType::RIGHT_PAREN);
}

void DatalogProgram::parsePredicateList(TokenList &input, Rule *r){
    TokenType currType = input.at(index)->getType();
    if(tokenInSet(FIRST_list, FIRST_list_c, currType)){
        parseTerminal(input, TokenType::COMMA);

        Predicate *p;
        parsePredicate(input, p);
        r->addPredicate(p);

        parsePredicateList(input, r);
    }else if(!tokenInSet(FOLLOW_predicateList, FOLLOW_predicateList_c, currType)){
        throw -6;
    }
}
void DatalogProgram::parseParameterList(TokenList &input, Predicate *p){
    TokenType currType = input.at(index)->getType();
    if(tokenInSet(FIRST_list, FIRST_list_c, currType)){
        parseTerminal(input, TokenType::COMMA);
        parseParameter(input, p);
        parseParameterList(input, p);
    }else if(!tokenInSet(FOLLOW_list, FOLLOW_list_c, currType)){
        throw -7;
    }
}

void DatalogProgram::parseStringList(TokenList &input, Predicate *p){
    TokenType currType = input.at(index)->getType();
    if(tokenInSet(FIRST_list, FIRST_list_c, currType)){
        parseTerminal(input, TokenType::COMMA);
        parseTerminal(input, TokenType::STRING);
        domain.insert(input[index-1]->getDescription());
        p->addParameter(new Parameter(input[index-1]->getDescription(),
                                        input[index-1]->getType() == TokenType::STRING));
        
        parseStringList(input, p);
    }else if(!tokenInSet(FOLLOW_list, FOLLOW_list_c, currType)){
        throw -8;
    }
}


void DatalogProgram::parseIdList(TokenList &input, Predicate *p){
    TokenType currType = input.at(index)->getType();
    if(tokenInSet(FIRST_list, FIRST_list_c, currType)){
        parseTerminal(input, TokenType::COMMA);
        parseTerminal(input, TokenType::ID);
        p->addParameter(new Parameter(input[index-1]->getDescription(),
                                        input[index-1]->getType() == TokenType::STRING));

        parseIdList(input, p);
    }else if(!tokenInSet(FOLLOW_list, FOLLOW_list_c, currType)){
        throw -9;
    }
}
void DatalogProgram::parseParameter(TokenList &input, Predicate *p){
    TokenType currType = input.at(index)->getType();
    if(tokenInSet(FIRST_parameter, FIRST_parameter_c, currType)){
        p->addParameter(new Parameter(input[index]->getDescription(),
                                        input[index]->getType() == TokenType::STRING));
        index++;
    }else{
        throw -10;
    }
}

void DatalogProgram::parseTerminal(TokenList &input, TokenType type){
    if(input.at(index)->getType() == type){
        index++;
    }else{
        // std::cout << "Failed to parse token " << *input.at(index) << std::endl;
        throw -1;
    }
}

// ############################################################################
// UTILS
// ############################################################################

bool DatalogProgram::tokenInSet(const TokenType *set, int setc, TokenType &comp){
    for(int i = 0; i < setc; i++){
        if(*(set+i) == comp)
            return true;
    }
    return false;
}

// ############################################################################
// SERIALIZING FUNCTIONS
// ############################################################################


std::string DatalogProgram::toString() const {
    std::ostringstream oss;

    oss << "Schemes(" << schemes.size() << "):" << std::endl;
    for(auto s : schemes){
        oss << "  " << *s << std::endl;
    }

    oss << "Facts(" << facts.size() << "):" << std::endl;
    for(auto f : facts){
        oss << "  " << *f << "." << std::endl;
    }

    oss << "Rules(" << rules.size() << "):" << std::endl;
    for(auto r : rules){
        oss << "  " << *r << "." << std::endl;
    }

    oss << "Queries(" << queries.size() << "):" << std::endl;
    for(auto q : queries){
        oss << "  " << *q << "?" << std::endl;
    }

    oss << "Domain(" << domain.size() << "):" << std::endl;
    if(!domain.empty()){
        oss << "  " << *domain.begin();
        for(std::set<std::string>::iterator it = ++domain.begin(); it != domain.end(); it++){ // will be a string, not a pointer
            oss << std::endl << "  " << *it;
        }
    }
    

    return oss.str();
}

std::ostream &operator<<(std::ostream &out, const DatalogProgram &dp){
    out << dp.toString();
    return out;
}

// ############################################################################
// ACCESSORS
// ############################################################################

std::vector<Predicate*> *DatalogProgram::getFacts(){ return &facts; }
std::vector<Predicate*> *DatalogProgram::getSchemes(){ return &schemes; }
std::vector<Predicate*> *DatalogProgram::getQueries(){ return &queries; }

// ############################################################################
// FIRST SETS
// ############################################################################

const TokenType DatalogProgram::FIRST_predicate[FIRST_predicate_c] 
    {TokenType::ID};
const TokenType DatalogProgram::FIRST_list[FIRST_list_c] 
    {TokenType::COMMA};
const TokenType DatalogProgram::FIRST_parameter[FIRST_parameter_c] 
    {TokenType::STRING, TokenType::ID};

// ############################################################################
// FOLLOW SETS
// ############################################################################

const TokenType DatalogProgram::FOLLOW_schemeList[FOLLOW_schemeList_c] 
    {TokenType::FACTS};
const TokenType DatalogProgram::FOLLOW_factList[FOLLOW_factList_c] 
    {TokenType::RULES};
const TokenType DatalogProgram::FOLLOW_ruleList[FOLLOW_ruleList_c] 
    {TokenType::QUERIES};
const TokenType DatalogProgram::FOLLOW_queryList[FOLLOW_queryList_c] 
    {TokenType::FILE_END};
const TokenType DatalogProgram::FOLLOW_predicateList[FOLLOW_predicateList_c] 
    {TokenType::PERIOD};
const TokenType DatalogProgram::FOLLOW_list[FOLLOW_list_c] 
    {TokenType::RIGHT_PAREN};


