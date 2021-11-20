#include "Elevator.h"
#include <iostream>

using namespace std;


   void Elevator::tick(int currentTime) {
    servicing = true;
    if(currentTime % TICKS_PER_ANGER_INCREASE == 0 && servicing){
        if(targetFloor > currentFloor){
            currentFloor++;
        }
        else if(targetFloor < currentFloor){
            currentFloor--;
        }
        
        
    }
    if(targetFloor == currentFloor){
        servicing = false;
    }

}

void Elevator::serviceRequest(int floorNum) {
    //TODO: Implement serviceRequest
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

void Elevator::print(ostream &outs) {
    outs << currentFloor;
    if (!servicing){
        outs << "w";
    } else {
        outs << "s" << targetFloor;
    }
}

Elevator::Elevator() {
    currentFloor = 0;
    servicing = false;
	targetFloor = 0;
}

void Elevator::setCurrentFloor(int currentFloorIn) {
    currentFloor = currentFloorIn;
}

bool Elevator::isServicing() const {
	return servicing;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

int Elevator::getTargetFloor() const {
    return targetFloor;
}
