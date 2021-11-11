#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "Predicate.h"
#include "Rule.h"

#include "../lexer/Token.h"
#define TokenList std::vector<Token*>


class DatalogProgram {
private:
    std::vector<Rule*> rules;
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    
    /*
    strings surrounded by quotes that appear in the facts.
    */
    std::set<std::string> domain;

    int index;

    // FIRST sets

    /*
    schemeList
    factList
    ruleList
    queryList
    scheme
    fact
    rule
    query
    headPredicate
    predicate
    */
    static const int FIRST_predicate_c = 1;
    static const TokenType FIRST_predicate[FIRST_predicate_c]; // ID

    /*
    predicateList
    parameterList
    stringList
    idList
    */
    static const int FIRST_list_c = 1;
    static const TokenType FIRST_list[FIRST_list_c];

    /*
    parameter
    */
    static const int FIRST_parameter_c = 2;
    static const TokenType FIRST_parameter[FIRST_parameter_c];

    // FOLLOW sets:
    
    static const int FOLLOW_schemeList_c = 1;
    static const TokenType FOLLOW_schemeList[FOLLOW_schemeList_c];

    static const int FOLLOW_factList_c = 1;
    static const TokenType FOLLOW_factList[FOLLOW_factList_c];

    static const int FOLLOW_ruleList_c = 1;
    static const TokenType FOLLOW_ruleList[FOLLOW_ruleList_c];

    static const int FOLLOW_queryList_c = 1;
    static const TokenType FOLLOW_queryList[FOLLOW_queryList_c];

    static const int FOLLOW_predicateList_c = 1;
    static const TokenType FOLLOW_predicateList[FOLLOW_predicateList_c];

    /*
    parameterList
    stringList
    idList
    */
    static const int FOLLOW_list_c = 1;
    static const TokenType FOLLOW_list[FOLLOW_list_c];

    // parse functions
    /*
    Only some of these functions will add elements to the predicate lists above.
    The rest will return values to build the predicates.
    */


    void parseDatalogProgram(TokenList &input);

    void parseSchemeList(TokenList &input);
    void parseFactList(TokenList &input);
    void parseRuleList(TokenList &input);
    void parseQueryList(TokenList &input);

    void parseScheme(TokenList &input); // adds a scheme to schemes
    void parseFact(TokenList &input);   // adds a fact to facts
    void parseRule(TokenList &input);   // adds a rule to rules
    void parseQuery(TokenList &input);  // adds a query to queries

    /*
    @param headPredicate: the predicate to be used as the head for a Rule. 
    Will be initialized in the function, so pass by reference.
    */
    void parseHeadPredicate(TokenList &input, Predicate *&headPredicate);
    /*
    @param p: an object to hold the data structure of the predicate being passed. 
    Will be initialized in the function, so pass by reference.
    */
    void parsePredicate(TokenList &input, Predicate *&p);

    void parsePredicateList(TokenList &input, Rule *r);
    void parseParameterList(TokenList &input, Predicate *p);

    void parseStringList(TokenList &input, Predicate *p);
    void parseIdList(TokenList &input, Predicate *p);
    void parseParameter(TokenList &input, Predicate *p);

    void parseTerminal(TokenList &input, TokenType type);

    // utils
    /*
    Checks to see if a tokentype is in a given FIRST or FOLLOW set. 
    It's really just a simple search function that could be templated.
    @param set: the follow/first set in question
    @param setc: the size of set
    @param comp: the tokentype being checked
    @return whether comp is in set
    */
    static bool tokenInSet(const TokenType *set, int setc, TokenType &comp);

public:
    DatalogProgram();
    ~DatalogProgram();

    /*
    Starts the parsing of the datalog program
    @param input: the token list given by the lexer
    @param showSuccessOutput: a boolean to determine whether or not to display output upon a successful run of the parser. (false by default)
    */
    void start(TokenList &input, bool showSuccessOutput=false);

    std::vector<Predicate*> *getSchemes();
    std::vector<Predicate*> *getFacts();
    std::vector<Predicate*> *getQueries();

    // serialization
    std::string toString() const;
    friend std::ostream &operator<<(std::ostream &out, const DatalogProgram &dp);

};


#endif /* DATALOGPROGRAM_H */
