#ifndef DATABASE_H
#define DATABASE_H

#include "Relation.h"

#include <map>
#include <string>

class Database {
private:
    std::map<std::string_view /* name of relation */, Relation*> database;
public:
    Database();
    ~Database();

    /*
    Adds a relation to the relation database
    @param relation: the relation to be added
    */
    void addRelation(std::string &name, Relation *relation);

    /*
    Gets a relation by its name
    @param name: a pointer to the name of the relation. Storing the strings as pointers 
    is faster since we can't use a hash map and since it means we only have to compare
    memory addresses.
    @return The relation with the given name
    */
    Relation *getRelation(std::string &name);
};

#endif /* DATABASE_H */