#include "Relation.h"

#include <iostream>
#include <sstream>

Relation::Relation() {}
Relation::Relation(std::string name, Header *header): name(std::move(name)), header(header) {}
Relation::~Relation(){}

void Relation::addInstance(Tuple *instance){
    if(instance->getLength() == header->getLength()){
        instances.insert(instance);
    }else{
        std::cerr << "Failed to add instance; Tuple not the same size as header." << std::endl;
    }
}
bool Relation::performUnion(Relation *r){
    bool result = false;

    std::ostringstream tupleStream;
    for(auto instance : *r){
        if(instances.insert(instance).second){ // true if new element inserted
            serializeTuple(tupleStream, instance, instance->getLength());
            tupleStream << std::endl;
            std::cout << tupleStream.str();
            tupleStream.clear();

            result = true;
        }
    }
    return result;
}

bool Relation::containsInstance(Tuple *instance){
    for(Tuple *t : instances){
        if(*t == *instance){
            return true;
        }
    }
    return false;
}



Relation *Relation::select(unsigned int index, std::string &value) const {
    Relation *r = new Relation(name, header);
    for(auto i : instances){
        if(value == i->getValue(index)){
            r->addInstance(i);
        }
    }
    return r;
}
Relation *Relation::select(int a, int b) const {
    Relation *r = new Relation(name, header);
    for(auto i : instances){
        if(i->getValue(a) == i->getValue(b)){
            r->addInstance(i);
        }
    }
    return r;
}

Relation *Relation::project(const std::vector<int> &indices) const {
    Header *h = new Header();
    Relation *r = new Relation(name, h);

    for(int i : indices){
        h->addAttribute(header->getAttribute(i));
    }

    for(auto instance : instances){
        Tuple *t = new Tuple();
        for(int j : indices){
            t->addValue(instance->getValue(j));
        }
        if(!r->containsInstance(t))
            r->addInstance(t);
        else
            delete t;
    }
    return r;
}
Relation *Relation::project(const std::set<int> &indices) const {
    std::vector<int> result;
    for(auto i : indices){
        result.push_back(i);
    }
    return project(result);
}

Relation *Relation::rename(std::unordered_map<std::string_view, int> &attributes) const {
    Header *h = new Header();
    *h = *header;
    Relation *r = new Relation(name, h);
    
    for(auto it = attributes.begin(); it != attributes.end(); it++){
        h->setAttribute(it->first, it->second);
    }
    for(auto i : instances){
        r->addInstance(i);
    }
    
    return r;
}
Relation *Relation::join(Relation *rhs) const{
    // joins any two tables on any common columns
    // i.e. perform intersection on any common schema 
    //      and append relevant rows from other columns


    // <index of second relation, index of first relation>
    std::unordered_map<int, int> commonSchema;
    for(unsigned int indexLHS = 0; indexLHS < this->header->getLength(); indexLHS++){
        int indexRHS = rhs->header->findAttribute(header->getAttribute(indexLHS));
        if(indexRHS != -1){ // if the attribute in `relation a` is also an attribute in `relation b`
            commonSchema[indexRHS] = indexLHS; // link them in the map.
        }
    }

    std::vector<int> uniqueIndices; // these are the indices of all unique columns in the RHS relation of the join
    for(unsigned int i = 0; i < rhs->header->getLength(); i++){
        if(!commonSchema.count(i)){
            uniqueIndices.push_back(i);
        }
    }

    // build the header
    Header *header = joinHeaders(this->header, rhs->header, uniqueIndices);

    // create the relation
    Relation *result = new Relation(name, header);

    // add all instances that match and their corresponding columns to a new relation containing everything
    for(auto instanceLHS : instances){
        for(auto instanceRHS : *rhs){
            if(canJoin(rhs, instanceLHS, instanceRHS, commonSchema)){
                Tuple *t = joinTuples(instanceLHS, instanceRHS, uniqueIndices);
                
                result->addInstance(t);

            }
        }
    }
    return result;
}
bool Relation::canJoin(Relation *rhs, Tuple *t1, Tuple *t2, std::unordered_map<int,int> &commonSchema) const {
    for(auto link : commonSchema){
        if(t1->getValue(link.second) != t2->getValue(link.first)){
            return false;
        }
    }
    /*
    notice this will always return true when commonSchema.size() is 0.
    Thus, if we have no common schema between the two tables, join() will
    peform the cross product of the two relations.
    */
    return true;
}
Tuple *Relation::joinTuples(Tuple *t1, Tuple *t2, std::vector<int> &t2Indices) {
    Tuple *result = new Tuple();
    for(unsigned int i = 0; i < t1->getLength(); i++){
        result->addValue(t1->getValue(i));
    }
    for(int i : t2Indices){
        result->addValue(t2->getValue(i));
    }
    return result;
}
Header *Relation::joinHeaders(Header *h1, Header *h2, std::vector<int> &h2Indices){
    Header *result = new Header();
    for(unsigned int i = 0; i < h1->getLength(); i++){
        result->addAttribute(h1->getAttribute(i)); // we add everything from our current relation
    }
    for(auto i : h2Indices){
        result->addAttribute(h2->getAttribute(i)); // we add all unique columns of the second relation
    }
    return result;
}

std::string Relation::getName() const { return name; }
std::string Relation::toString() const {
    int length = header->getLength();
    if( 
        isEmpty() // this shouldn't ever be the case
        || length == 0 // if this is the case, there were no variables in our query. thus, we don't have to print anything
    ){
        return "";
    }

    /*
    turns out it's super easy you just needa define a custom compare function for the set.
    If you're confused about this comment, read the previous commit.
    */

    std::ostringstream result;
    for (Tuple *t : instances){
        serializeTuple(result, t, length);
        result << std::endl;
    }
    return result.str();
}
std::ostream &Relation::serializeTuple(std::ostream &out, Tuple *t, int length) const{
    out << "  ";
        for(int i = 0; i < length-1; i++){
            out << header->getAttribute(i) << "=" << t->getValue(i) << ", ";
        }
    out << header->getAttribute(length-1) << "=" << t->getValue(length-1);
    return out;
}


std::ostream &operator<<(std::ostream &out, const Relation &r) {
    out << r.toString();
    return out;
}