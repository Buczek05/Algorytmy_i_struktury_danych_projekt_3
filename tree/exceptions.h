#pragma once
#include <iostream>

class MyBaseException : public std::exception {
public:
    MyBaseException() {};
    MyBaseException(const std::string &message) : msg_(message) {}

    virtual char const *what() const throw() {
        return msg_.c_str();
    }

protected:
    std::string msg_ = "EMPTY";
};


class NotFoundElementException : public MyBaseException {
protected:
    std::string msg_ = "Not found element";
};

class PopElementIsRoot : public MyBaseException {
protected:
    std::string msg_ = "";
};