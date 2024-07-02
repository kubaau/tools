#pragma once

#include "Print.hpp"

class Loud
{
public:
    Loud(int i) : id(i) { print("ctor", id); }
    ~Loud() { print("dtor", id); }
    Loud(const Loud& rhs) : id(rhs.id) { print("copyctor", id); }
    Loud& operator=(const Loud& rhs)
    {
        id = rhs.id;
        print("copyassop", id);
        return *this;
    }
    Loud(Loud&& rhs) : id(rhs.id) { print("movector", id); }
    Loud& operator=(Loud&& rhs)
    {
        id = rhs.id;
        print("moveassop", id);
        return *this;
    }
    Loud& operator++()
    {
        print("preincr", id);
        ++id;
        return *this;
    }
    Loud operator++(int)
    {
        print("postincr", id);
        auto temp{*this};
        ++id;
        return temp;
    }
    operator int() { return id; }

private:
    int id = 0;
};
