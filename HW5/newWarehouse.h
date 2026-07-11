#ifndef NEWWAREHOUSE_H
#define NEWWAREHOUSE_H

#include "Cargo.h"
#include <vector>
#include <algorithm>
#include <iostream>

class newWarehouse{
protected:
    std::vector<Cargo> cargos;
    int time_counter;

public:
    newWarehouse() : time_counter(0){}

    newWarehouse& operator+(Cargo& c){
        c.timestamp = time_counter++;
        cargos.push_back(c);
        
        std::push_heap(cargos.begin(), cargos.end(), [](const Cargo& a, const Cargo& b){
            if(a.priority != b.priority){
                return a.priority < b.priority; 
            }
            return a.timestamp > b.timestamp;   
        });
        
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const newWarehouse& w){
        newWarehouse temp = w;
        std::sort(temp.cargos.begin(), temp.cargos.end(), [](const Cargo& a, const Cargo& b){
            if(a.priority != b.priority){
                return a.priority > b.priority;
            }
            return a.timestamp < b.timestamp;
        });
        for(const auto& c : temp.cargos){
            os << c.location << " " << c.content << " " << c.priority << "\n";
        }
        return os;
    }

    newWarehouse& operator--(){
        if(!cargos.empty()){
            std::pop_heap(cargos.begin(), cargos.end(), [](const Cargo& a, const Cargo& b){
                if(a.priority != b.priority){
                    return a.priority < b.priority; 
                }
                return a.timestamp > b.timestamp;   
            });
            cargos.pop_back();
        }
        return *this;
    }

    newWarehouse operator--(int){
        newWarehouse temp = *this;
        --(*this);
        return temp;
    }
};

#endif