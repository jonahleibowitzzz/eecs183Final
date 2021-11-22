#include "Building.h"

using namespace std;

void Building::spawnPerson(Person newPerson){
    int x = newPerson.getCurrentFloor();
    int y = newPerson.getTargetFloor();
    if(x <= 9 && x >= 0){
        if(y <= 9 && y >= 0){
            int z;
            if(x > y){
                 z = -1;
            }
            else {
            z = 1;
            }
            floors[x].addPerson(newPerson, z);
        }
    }
}

void Building::update(Move move){
    if(move.isPickupMove()){
        int pickupCopy[move.getNumPeopleToPickup()];
        move.copyListOfPeopleToPickup(pickupCopy);
        
        //removes people from target floor
        floors[move.getTargetFloor()].removePeople(pickupCopy, move.getNumPeopleToPickup());
    }
    
    if(!move.isPassMove()){
        elevators[move.getElevatorId()].serviceRequest(move.getTargetFloor());
    }

}

int Building::tick(Move move){
    time++;
    update(move);
    
    //tick elevators
    for(int i = 0; i < NUM_ELEVATORS; i++){
        elevators[i].tick(time);
    }
    
    int exploded = 0;
    //tick floors/people
    for(int j = 0; j < NUM_FLOORS; j++){
        exploded += floors[j].tick(time);
        for(int k = 0; k < floors[j].getNumPeople(); k++)
            floors[j].getPersonByIndex(k).tick(time);
    }

    return exploded;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Building::Building() {
    time = 0;
}

void Building::setElevator(string elevatorInfo, int elevatorId) {
    int i = 0;
    string currPosString = "";
    string destPosString = "";

    while(elevatorInfo[i] != 's' && elevatorInfo[i] != 'w'){
        currPosString += elevatorInfo[i];
        i++;
    }
    elevators[elevatorId] = Elevator();

    elevators[elevatorId].setCurrentFloor(stoi(currPosString));

    if (elevatorInfo[i] == 's') {
        i++;
        while (i < (int)elevatorInfo.size()) {
            destPosString += elevatorInfo[i];
            i++;
        }
        elevators[elevatorId].serviceRequest(stoi(destPosString));
    }
}

int Building::getTime() const {
    return time;
}

void Building::setTime(int timeIn) {
    time = timeIn;
}

void Building::prettyPrintBuilding(ostream& outs) const {
    //-------
    //| | | | 🔼 1 4 2
    //| | |E| 🔽 o o o
    //-------
    //| | | | 🔼   1
    //| |E| |      o
    //-------
    //| | | |
    //|E| | |
    for (int i = NUM_FLOORS - 1; i >= 0; --i) {
            outs << "   ";
            for (int j = 0; j < 2 * NUM_ELEVATORS + 1; ++j) {

                outs << '-';
            }

            outs << endl << "   ";

            for (int j = 0; j <  NUM_ELEVATORS; ++j) {
                char floorIndicatorIcon = ' ';

                if (elevators[j].getCurrentFloor() == i &&
                    elevators[j].isServicing()) {

                    char floorServiceIndicator = ('0' + elevators[j].getTargetFloor());
                    floorIndicatorIcon = floorServiceIndicator;
                }

                outs << "|" << floorIndicatorIcon;
            }
            outs << "|";

            floors[i].prettyPrintFloorLine1(outs);
            outs << i << "  ";
            for (int j = 0; j <  NUM_ELEVATORS; ++j) {

                outs << "|" << (elevators[j].getCurrentFloor() == i ? 'E' : ' ');
            }
            outs << "|";

            floors[i].prettyPrintFloorLine2(outs);
        }
        outs << "   ";
        for (int j = 0; j < 2 * NUM_ELEVATORS + 1; ++j) {
            outs << '-';
        }
        outs << endl << "   ";
        for (int j = 0; j < NUM_ELEVATORS; ++j) {
            outs << " " << j;
        }
        outs << endl;
}

Elevator Building::getElevatorById(int elevatorId) const {
    return elevators[elevatorId];
}

Floor Building::getFloorByFloorNum(int floorNum) const {
    return floors[floorNum];
}

BuildingState Building::getBuildingState() const {
    BuildingState buildingState;
    buildingState.turn = time;

    for (int i = 0; i < NUM_FLOORS; ++i) {
        buildingState.floors[i].floorNum = i;
        buildingState.floors[i].hasDownRequest = floors[i].getHasDownRequest();
        buildingState.floors[i].hasUpRequest = floors[i].getHasUpRequest();

        int & np = buildingState.floors[i].numPeople;

        for (int j = 0; j < floors[i].getNumPeople(); ++j) {

            Person p = floors[i].getPersonByIndex(j);
            buildingState.floors[i].people[np++].angerLevel = p.getAngerLevel();
        }
    }

    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        Elevator e = elevators[i];

        buildingState.elevators[i].elevatorId = i;
        buildingState.elevators[i].targetFloor = e.getTargetFloor();
        buildingState.elevators[i].currentFloor = e.getCurrentFloor();
        buildingState.elevators[i].isServicing = e.isServicing();
    }

    return buildingState;
}
