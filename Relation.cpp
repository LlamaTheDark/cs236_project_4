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

Relation *Relation::project(const std::set<int> &indices) const {
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

std::string Relation::getName() const {
    return name;
}

std::string Relation::toString() const {
    int length = header->getLength();
    if( 
        isEmpty() // this shouldn't ever be the case
        || length == 0 // if this is the case, there were no variables in our query. thus, we don't have to print anything
    ){
        return "";
    }

    /*
    If you're reading this, you've found the part of the code that sorts the
    set that is supposed to sort itself (supposedly. obviously if it worked we wouldn't be here).
    I have not been able to find the set contained in each Relation object fails to
    sort itself correctly. In a seperate, one file test I have tried but been unsuccessful
    in even recreating the issue. In every case that I tried, it works. This includes the case
    of storing my tuples as pointers in the set. So until I figure that out (as I likely will
    before I turn in project 4) I'm stuck with manually sorting the tuples before I print them
    to the output. I don't like it any more than you do. I'm sure it's something super stupid
    and I'm gonna laugh real long and hard at myself for not getting it.

    I'm compiling with g++, debugging with gdb, and have tested it on a seperate linux server I have running. idk man.

    I also tried changing the < overload operator to accept a reference to a pointer but it no work.
    I suppose because it's doing comparison for Tuple to Tuple* which isn't even what the set is supposed to do
    but it doesn't let you define a comparison operator for Tuple* and Tuple* so BRUH idk what to do.

    Okay yeah so the problem is that I'm storing pointers to Tuples instead of tuples themselves.
    I'm sure I could have done this better but I'm too deep down the pointer train
    there's no stopping me now

    Yeah I gotta find a way to change how the set's compare function works with it's OWN
    ELEMENTS AAAUGH.

    Thing is when I did it in another file it worked perfectly fine pointers and all. Maybe I'm
    just going insane.

    Alright well this works so I'm going to sleep.
    */

   std::set<Tuple> instances;
   for(auto instance : this->instances){
       instances.insert(*instance);
   }

    std::ostringstream result;
    for (Tuple t : instances){
        result << "  ";
        for(int i = 0; i < length-1; i++){
            result << header->getAttribute(i) << "=" << t.getValue(i) << ", ";
        }
        result << header->getAttribute(length-1) << "=" << t.getValue(length-1);
        result << std::endl;
    }
    return result.str();
}

std::ostream &operator<<(std::ostream &out, const Relation &r) {
    out << r.toString();
    return out;
}