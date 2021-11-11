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
    /*
    @param attributes: A map which maps a pointer to a parameter to an int. Each parameter is
    an attribute that should be added to the header at the specified index. For each index not
    in the map, the header just uses it's original attribute.
    @return A new relation with the header changed to the new list of attribtues
    */
    Relation *rename(std::unordered_map<std::string_view, int> &attributes) const;

    bool isEmpty() const { return instances.empty(); }
    int getInstanceCount() const { return instances.size(); }

    std::string getName() const;
    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &out, const Relation &r);
};

#endif /* RELATION_H */