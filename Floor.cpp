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
    
    removePeople(exploded, explodeCount);
    
    return explodeCount;
}

void Floor::addPerson(Person p, int request) {
    if(numPeople < MAX_PEOPLE_PER_FLOOR){
        people[numPeople] = p;
        numPeople++;
    }
    
    if (request > 0) {
        hasUpRequest = true;
    }
    else if (request < 0) {
        hasDownRequest = true;
    }
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    /*
     What we need to do:
     Given:
     Array of people objects
     Number index for each person
     List of indices to be removed (not always in order)
     
     Remove each of the indicated people
     Close list so there is no white space
     
     Plan:
     SECOND SOLUTION
     For loop the number of times of numPeopleToRemove
     Erase single person, back the remaining items up
        Create for loop starting at index to remove, equals everything back one index. Last index set to 0
        
     
     Update numPeople
     Reassess up/down requests at the end using function
     
     Tester:
     cout << "ORIGINAL:" << endl;
     for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++) {
         cout << "Person " << i << " turn: " << people[i].getTurn() << endl;
     }
     */
    
    
    ///Blank all indicated indices
    Person blank;
    for(int i = 0; i < numPeopleToRemove; i++){
        people[indicesToRemove[i]] = blank;
    }
    
    ///USE THIS TO BACK EVERYTHING UP SO THERE'S NO HOLES
    for(int k = 0; k < numPeopleToRemove; k ++){
        for(int i = 0; i < numPeople; i++){
            if(people[i].getTurn() == 0 && people[i].getAngerLevel() == 0 &&
               people[i].getTargetFloor() == 0 && people[i].getCurrentFloor() == 0){
                for(int j = i; j < numPeople; j++){ //ISSUES WHEN ALL 10 ARE FILLED?
                    people[j] = people[j + 1];
                }
            }
        }
    }
    numPeople -= numPeopleToRemove;
    resetRequests();
}

void Floor::resetRequests() {
    hasUpRequest = false;
    hasDownRequest = false;
    for(int i = 0; i < numPeople; i++){
        if (getPersonByIndex(i).getTargetFloor() > getPersonByIndex(i).getCurrentFloor()) {
            hasUpRequest = true;
        }
        if (getPersonByIndex(i).getTargetFloor() < getPersonByIndex(i).getCurrentFloor()){
            hasDownRequest = true;
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
