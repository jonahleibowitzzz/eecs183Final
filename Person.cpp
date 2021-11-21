#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;



    
Person::Person(string input_string) : Person() {
    int i = 0;
    int turnCount = 0;
            
    while(input_string.at(i) >= 48 && input_string.at(i) <= 57){
        turnCount++;
        i++;
    }
    for (int j = 0; j < turnCount; j++) {
        turn += (input_string.at(j) - '0') * pow(10, turnCount - 1 - j);
    }
    
    currentFloor = input_string.at(turnCount + 1) - '0';
    targetFloor = input_string.at(turnCount + 3) - '0';
    angerLevel = input_string.at(turnCount + 5) - '0';
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
    outs << "f" << currentFloor << "t" << targetFloor << "a" <<angerLevel;
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
