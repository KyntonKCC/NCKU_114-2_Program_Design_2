#include <iostream>
#include "Cargo.h"
#include "Warehouse.h"

using namespace std;

int main(){
    int N;
    if(cin >> N){
        Warehouse w;
        for(int i = 0; i < N; ++i){
            Cargo c;
            cin >> c;
            if(c == "Collaboration"){
                ++c;
            }
            w + c;
        }
        cout << w;
    }
    return 0;
}