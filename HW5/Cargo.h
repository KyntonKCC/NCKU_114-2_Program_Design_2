#ifndef CARGO_H
#define CARGO_H

#include <iostream>
#include <string>
using namespace std;

class Cargo{
public:
    string location;
    string content;
    int priority;
    int timestamp;

    Cargo() : priority(0), timestamp(0){}

    friend istream& operator>>(istream& is, Cargo& c){
        is >> c.location >> c.content >> c.priority;
        return is;
    }

    bool operator==(const string& target) const{
        return content == target;
    }

    Cargo& operator++(){
        priority++;
        return *this;
    }

    Cargo operator++(int){
        Cargo temp = *this;
        priority++;
        return temp;
    }
};

#endif