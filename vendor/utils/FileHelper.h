#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class FileHelper {
public:
    static bool write(const std::string &filename, const std::string &content) {
        std::ofstream ofs;
        ofs.open(filename, std::ios::out | std::ios::trunc);
        if(ofs.is_open()){
            ofs << content;
            ofs.close();
        }else{
            return false;
        }

        return true;
    }
};


#endif /* FILEHELPER_H */