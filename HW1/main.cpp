#include <iostream>
#include <string>
#include "Elevator.h"

using namespace std;

int main() {
    Elevator elevator(500);
    string command;
    int value;

    while (cin >> command) {
        if (command == "enter") {
            cin >> value;
            elevator.updateWeight(value);
        } else if (command == "leave") {
            cin >> value;
            elevator.updateWeight(-value);
        } else if (command == "move") {
            cin >> value;
            elevator.move(value);
        } else if (command == "open") {
            elevator.openDoor();
        } else if (command == "close") {
            elevator.closeDoor();
        } else if (command == "display") {
            elevator.displayStatus();
        }
    }
    return 0;
}
