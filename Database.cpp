#include <iostream>

#include "Database.h"

Database::Database(){}
Database::~Database(){
    auto it = database.begin();
    while(it != database.end()){
        delete it->second;
        it++;
    }
}

void Database::addRelation(std::string &name, Relation *relation){
    database[name] = relation;
}

Relation *Database::getRelation(std::string &name) {
    for(auto it : database){
        if(it.first == name){
            return it.second;
        }
    }
    std::cerr << "ERROR: Attempted to get relation with name \'" << name << "\' when none exists." << std::endl;
    return NULL;
}