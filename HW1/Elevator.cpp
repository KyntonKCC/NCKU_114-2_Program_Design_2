#include "Elevator.h"

using namespace std;

static int curr_floor = 1;
static int curr_weight = 0;
static bool door_open = false;

// name 
Elevator::Elevator(int limit):weightLimit(limit)
{
    // write your codes here...
    curr_floor = 1;
    curr_weight = 0;
    door_open = false;
}
void Elevator::updateWeight(int weight) 
{
    // write your codes here...
    if(door_open){
        curr_weight += weight;
        if(curr_weight < 0)
            curr_weight = 0;
        if(curr_weight > 10000)
            curr_weight = 10000;
    }
}
void Elevator::openDoor()
{
    // write your codes here...    
    door_open = true;
}
void Elevator::closeDoor()
{
    // write your codes here...    
    if(curr_weight > weightLimit){
        cout << "[Elevator System] Overweight! Door cannot close." << endl;
        door_open = true;
    }else{
        door_open = false;
    }
}
void Elevator::move(int floor)
{
    // write your codes here...  
    if(floor < 1 || floor > 10){
        cout << "[Elevator System] Invalid floor! Ericvator only serves 1F to 10F." << endl;
        return;
    }
    if(door_open){
        cout << "[Elevator System] Danger! Close the door before moving." << endl;
        return;
    }
    if(curr_weight > weightLimit){
        return; 
    }
    curr_floor = floor;
}
void Elevator::displayStatus()
{
    // write your codes here...  
    cout << "[Elevator System] Ericvator at " << curr_floor << "F, ";
    cout << "Weight: " << curr_weight << " kg (limit: 500 kg), ";
    cout << "Door: " << (door_open ? "Open" : "Closed") << ", ";
    cout << "Overloaded: " << (curr_weight > weightLimit ? "Yes" : "No") << endl;
}
