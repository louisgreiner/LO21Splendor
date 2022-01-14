#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

class Exception{
    private:
        std::string info;
    public:
        Exception(const std::string& i): info(i) {} // DONE
        std::string getInfo() const { return info;} // DONE
};

#endif // EXCEPTION_H
