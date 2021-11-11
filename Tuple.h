#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>

class Tuple {
private:
    std::vector<std::string_view> values;
public:
    Tuple();

    unsigned int getLength();

    void addValue(std::string_view value);
    std::string_view getValue(int index) const;

    bool operator<(const Tuple &rhs) const {
        return values < rhs.values;
    }
    bool operator==(const Tuple &rhs) const {
        for(unsigned int i = 0; i < values.size(); i++){
            if(values.at(i) != rhs.getValue(i)){
                return false;
            }
        }
        return true;
    }

    
};

#endif /* TUPLE_H */