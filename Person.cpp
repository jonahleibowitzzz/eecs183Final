#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Person::Person(string input_string) : Person() {
    turn = input_string.at(0) - '0';
    currentFloor = input_string.at(2) - '0';
    targetFloor = input_string.at(4) - '0';
    angerLevel = input_string.at(6) - '0';
}

bool Person::tick(int currentTime) {
    if(currentTime % TICKS_PER_ANGER_INCREASE == 0){
        angerLevel++;
    }
    if(angerLevel >= MAX_ANGER){
        return true;
    }
    return false;
}
    
void Person::print(ostream &outs) {    
    //TODO: Implement print
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
