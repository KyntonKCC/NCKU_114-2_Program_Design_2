#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "Cargo.h"
#include "Warehouse.h"
#include "newWarehouse.h"

using namespace std;

int main(){
    vector<Cargo> inputs;
    Cargo c;
    
    while(cin >> c){
        inputs.push_back(c);
    }

    Warehouse w1;
    auto start1 = chrono::high_resolution_clock::now();
    for(auto& item : inputs){
        w1 = w1 + item;
    }
    auto end1 = chrono::high_resolution_clock::now();
    double time1 = chrono::duration<double>(end1 - start1).count();

    newWarehouse w2;
    auto start2 = chrono::high_resolution_clock::now();
    for(auto& item : inputs){
        w2 = w2 + item;
    }
    auto end2 = chrono::high_resolution_clock::now();
    double time2 = chrono::duration<double>(end2 - start2).count();

    cout << "----------------------------------------\n";
    cout << fixed << setprecision(3);
    cout << "Warehouse takes: " << time1 << " seconds\n";
    cout << "newWarehouse takes: " << time2 << " seconds\n";
    cout << "----------------------------------------\n";
    
    if(time1 > time2){
        cout << "newWarehouse is faster by " << (time1 - time2) << " seconds!\n";
    }else{
        cout << "Warehouse is faster by " << (time2 - time1) << " seconds!\n";
    }

    return 0;
}