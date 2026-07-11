#include <iostream>
#include "Cargo.h"
#include "Warehouse.h"

using namespace std;

int main(){
    int choice;
    Warehouse w;

    while(cin >> choice){
        if(choice == 1){
            int N;
            cin >> N;
            for (int i = 0; i < N; ++i){
                Cargo c;
                cin >> c;
                w + c;
            }
        }else if(choice == 2){
            --w;
        }else if(choice == 0){
            cout << w;
            break;
        }
    }
    return 0;
}