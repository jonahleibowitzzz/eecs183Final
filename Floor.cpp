#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    int explodeCount = 0;
    int exploded[MAX_PEOPLE_PER_FLOOR];
    for(int i = 0; i < numPeople; i++){
        if(getPersonByIndex(i).tick(currentTime)){
            exploded[explodeCount] = i;
            explodeCount++;
        }
    }
    
    removePeople(exploded, sizeof(exploded));
    
    return explodeCount;
}

void Floor::addPerson(Person p, int request) {
    if(numPeople < MAX_PEOPLE_PER_FLOOR){
        people[numPeople] = p;
    }
    
    if (request > 0) {
        hasUpRequest = true;
    }
    else if (request < 0) {
        hasUpRequest = false;
    }
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    //TODO: Implement removePeople
}

void Floor::resetRequests() {
    for(int i = 0; i < numPeople; i++){
        if (getPersonByIndex(i).getTargetFloor() > getPersonByIndex(i).getCurrentFloor()) {
            hasUpRequest = true;
        }
        else{
            hasUpRequest = false;
        }
        
        if (getPersonByIndex(i).getTargetFloor() < getPersonByIndex(i).getCurrentFloor()){
            hasDownRequest = true;
        }
        else{
            hasDownRequest = false;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
