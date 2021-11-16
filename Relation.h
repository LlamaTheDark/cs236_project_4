#ifndef RELATION_H
#define RELATION_H

#include "Header.h"
#include "Tuple.h"

#include <string>
#include <set>
#include <unordered_map>

class Relation {
private:
    std::string name;
    Header *header;
    std::set<Tuple*> instances;

    bool containsInstance(Tuple* instance);

    /*
    Tells you whether or not two tuples can be combined in a join
    @param ths: the right hand side relation being joined to this relation.
    @param t1: the tuple of this relation
    @param t2: the tuple of the rhs relation
    @param commonSchema: a map linking common columns of rhs and this relation.
                         A pair consists of <index in rhs relation, index in this relation>
    @return A boolean. true if the tuples should be combined, false otherwise.
    */
    bool canJoin(Relation *rhs, Tuple *t1, Tuple *t2, std::unordered_map<int, int> &commonSchema) const;
    /*
    Joins two tuples given specific indices to join for the second tuple
    @return a new tuple that is the result of joining the two tuples given
    */
    static Tuple *joinTuples(Tuple *t1, Tuple *t2, std::vector<int> &t2Indices);
    /*
    creates a header from two existing headers given the indices of attributes
    that should be added form the second header
    @return a new header that is the result of joining the two headers given
    */
    static Header *joinHeaders(Header *h1, Header *h2, std::vector<int> &h2Indices);
public:
    Relation();
    Relation(std::string name, Header *header);
    ~Relation();

    /*
    Adds an instance to the relation (i.e. adds another row to the table).
    @param instance: the tuple to be added
    */
    void addInstance(Tuple *instance);
    /*
    Adds all instances of parameter `r` to the relation from which the function was called.
    @param r: A pointer to the relation whose instances will be added to this
    @return a boolean saying whether any new tuples were added. true if tuple were added, false otherwise.
    */
    bool performUnion(Relation *r);

    /*
    Selects rows that contain a specific value for a given column
    @param index: relation column index
    @param value: value to select
    @return A new relation object with only the tuples selected.
    */
    Relation *select(unsigned int index, std::string &value) const;
    /*
    This function selects rows for which values in columns at indices colA and colB are the same.
    @param a: the first column whose values are to be compared with the second column
    @param b: the second column
    @return A new relation object which only contains the selected tuples
    */
    Relation *select(int a, int b) const;
    /*
    @param indices: A set containing the indices of each column to be projected.
    A set is used because it automatically sorts indices.
    @return A new relation with all but the specified columns removed.
    */
    Relation *project(const std::set<int> &indices) const;
    Relation *project(const std::vector<int> &indices) const;
    /*
    @param attributes: A map which maps a pointer to a parameter to an int. Each parameter is
    an attribute that should be added to the header at the specified index. For each index not
    in the map, the header just uses it's original attribute.
    @return A new relation with the header changed to the new list of attribtues
    */
    Relation *rename(std::unordered_map<std::string_view, int> &attributes) const;

    /*
    Performs natural join (i.e. |x|) on this relation and the relation passed.
    @param rhs: the right hand side relation to be joined to this relation.
    @return A new relation which is the result of a natural join between this and rhs.
    */
    Relation *join(Relation *rhs) const;

    bool isEmpty() const { return instances.empty(); }
    int instanceCount() const { return instances.size(); }

    std::string_view getAttribute(int index) { return header->getAttribute(index); }
    int headerLength() const { return header->getLength(); }

    std::string getName() const;
    std::string toString() const;
    std::ostream &serializeTuple(std::ostream &out, Tuple *t, int length) const;

    std::set<Tuple*>::iterator begin() { return instances.begin(); }
    std::set<Tuple*>::iterator end()   { return instances.end();   }

    friend std::ostream &operator<<(std::ostream &out, const Relation &r);
};

#endif /* RELATION_H */