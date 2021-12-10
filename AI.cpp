#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core
/*
 
 
* Requires: buildingState is a valid state representing the current building
* Modifies: Nothing
* Effects:  Returns a string that represents the decision the AI makes
*           given the current state of the building, which it reads
*           from buildingState.
*           The string should share the exact format as a
*           human player's move input.
*/
string getAIMoveString(const BuildingState& buildingState) {
    if(buildingState.turn==0){
        return "";
    }
    if(buildingState.elevators[0].isServicing && buildingState.elevators[1].isServicing && buildingState.elevators[2].isServicing){
        return "";
    }
    if(buildingState.floors[0].numPeople == 0 && buildingState.floors[1].numPeople == 0 &&buildingState.floors[2].numPeople == 0 &&buildingState.floors[3].numPeople == 0 &&buildingState.floors[4].numPeople == 0 &&buildingState.floors[5].numPeople == 0 &&buildingState.floors[6].numPeople == 0 &&buildingState.floors[7].numPeople == 0 &&buildingState.floors[8].numPeople == 0 &&buildingState.floors[9].numPeople == 0){
        return "";
    
}
    int x;
    for(int i = 0; i < NUM_FLOORS; ++i){
        int a; //floor at i
        int b; // floor at i-1
        //compare a and b and whatever one has most people store that into x (x keeps track of who has the most people
        //whatever floor has the most amount of people you store another integer x .
        //if x is null (not real floor) then compare a and b
        //compare a with x if x is not null (x is a real floor)
    
        if(buildingState.floors[i].numPeople > 0 )
            
    }
    
    return "";
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, const Floor& floorToPickup) {
    return "";
}
