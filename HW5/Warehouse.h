#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Cargo.h"
#include <vector>
#include <algorithm>
#include <iostream>

class Warehouse{
protected:
    vector<Cargo> cargos;
    int time_counter;

public:
    Warehouse() : time_counter(0){}

    Warehouse& operator+(Cargo& c){
        c.timestamp = time_counter++;
        cargos.push_back(c);
        
        sort(cargos.begin(), cargos.end(), [](const Cargo& a, const Cargo& b){
            if(a.priority != b.priority){
                return a.priority > b.priority;
            }
            return a.timestamp < b.timestamp;
        });
        
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Warehouse& w){
        for(const auto& c : w.cargos){
            os << c.location << " " << c.content << " " << c.priority << "\n";
        }
        return os;
    }

    Warehouse& operator--(){
        if(!cargos.empty()){
            cargos.erase(cargos.begin());
        }
        return *this;
    }

    Warehouse operator--(int){
        Warehouse temp = *this;
        if(!cargos.empty()){
            cargos.erase(cargos.begin());
        }
        return temp;
    }
};

#endif