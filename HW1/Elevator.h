#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <string>

class Elevator {
private:
    const std::string name = "Ericvator"; 
    const int weightLimit;
    // Define other private data members here...
    
public:
    // Initialize name and weight limit
    Elevator(int limit);

    // Update the current load weight
    void updateWeight(int weight);

    // Open the elevator door
    void openDoor();
    
    // Close the elevator door with safety check
    void closeDoor();

    // Move to the target floor if safe
    void move(int floor);
    
    // Output the current status of the elevator
    void displayStatus();
    
    // You can add functions if you need...
};

#endif
