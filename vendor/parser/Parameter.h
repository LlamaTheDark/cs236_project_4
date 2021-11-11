#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include <iostream>

class Parameter {
private:
    std::string content;
    bool constant; // strings are constant, IDs are variables
public:
    Parameter(std::string content, bool constant);
    ~Parameter();

    std::string *toString() { return &content; }
    std::string toString() const;

    bool isConstant() { return constant; }

    bool operator==(const Parameter &p) { return this->content == p.content; }
    bool operator!=(const Parameter &p) { return !(this->content == p.content); }
    bool operator<(const Parameter &p) { return this->content < p.content; }

    friend std::ostream &operator<<(std::ostream &out, const Parameter &p);
};

#endif /* PARAMETER_H */