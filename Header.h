#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>

class Header {
private:
    std::vector<std::string_view> attributes;
public:
    Header();

    void addAttribute(std::string_view attribute);
    void setAttribute(std::string_view attribute, int index);

    /*
    @param index: the index of the attribute whose name is desired
    @return a string_view of the attributes name
    
    */
    std::string_view getAttribute(int index);

    /*
    @param attribute: the attribute to be found
    @return the index of the attribute in the attribute vector
    or -1 if the attribute was not found.
    */
    int findAttribute(std::string_view attribute);

    unsigned int getLength();
};

#endif /* HEADER_H */