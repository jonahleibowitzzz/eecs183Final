#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Person::Person(string input_string) : Person() {
    //TODO: Implement non-default constructor
}

bool Person::tick(int currentTime) {
    bool Person::tick(int currentTime){
    int angerLevel = 0;
    if(currentTime % TICKS_PER_ANGER_INCREASE == 0){
        angerLevel = angerLevel + 1;
    }
    if(angerLevel >= MAX_ANGER){
        return true;
    }
    else {
    return false;
        
    }
    

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
