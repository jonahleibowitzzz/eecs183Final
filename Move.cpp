#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    if (commandString == ""){
        isPass = true;
    }
    else if(commandString.length() == 4){
        elevatorId = commandString.at(1) - '0';
        targetFloor = commandString.at(3) -'0';
    }
    else if(commandString.length() == 3){
        isPickup = true;
        elevatorId = commandString.at(1) -'0';
    }
    else if(commandString == "s" || commandString == "S"){
        isSave = true;
    }
    else if(commandString == "q" || commandString == "Q"){
        isQuit = true;
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if((isSave || isQuit || isPass) ||
       
       (isPickup && !elevators[elevatorId].isServicing() &&
          elevatorId < NUM_ELEVATORS && 0 <= elevatorId) ||
       
       (!isQuit && !isPass && !isPickup &&
        !elevators[elevatorId].isServicing() &&
        elevatorId < NUM_ELEVATORS && 0 <= elevatorId &&
        targetFloor != elevators[elevatorId].getCurrentFloor() &&
        targetFloor < NUM_FLOORS && 0 <= targetFloor
        )){
        return true;
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    for(int i = 0; i < pickupList.size(); i++){
        //peopleToPickup is a list of the indexes of the people to be picked up
        peopleToPickup[i] = pickupList.at(i) - '0';
        numPeopleToPickup++;
    }
    
    int angerLevel = 0;
    for(int k = 0; k < numPeopleToPickup; k++){
        angerLevel = pickupFloor.getPersonByIndex(peopleToPickup[k]).getAngerLevel();
        totalSatisfaction += MAX_ANGER - angerLevel;
    }
    
    int furthest = 0;
    for(int j = 0; j < numPeopleToPickup; j++){
      int distance =
        pickupFloor.getPersonByIndex(peopleToPickup[j]).getTargetFloor() -
        pickupFloor.getPersonByIndex(peopleToPickup[j]).getCurrentFloor();
        
        if (abs(distance) > furthest){
            furthest = abs(distance);
            targetFloor =
            pickupFloor.getPersonByIndex(peopleToPickup[j]).getTargetFloor();
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
