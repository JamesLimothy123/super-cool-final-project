/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Milan Charlakolu
 * charlakm
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString){
    int elevatorId = 0;
    int targetFloor = 0;
	bool isPass = false;
    bool isPickup = false;
    bool isSave = false;
    bool isQuit = false;

    if(commandString == "") {
        isPass = true;
    }
    else if(commandString == "s" || commandString == "S") {
        isSave = true;
    }
    else if(commandString == "q" || commandString == "Q") {
        isQuit = true;
    }
    else if (commandString.length() == 3) {
        isPickup = true;
        //subtract 48 to rezero char to actual integer
        elevatorId = commandString.at(1) - 48;
    }
    else if (commandString.length() == 4) {
        elevatorId = commandString.at(1) - 48;
        targetFloor = commandString.at(3) - 48;

        // for(int i = 0; i < commandString.length(); i++) {
        //     char c = commandString[i];
        //     tolower(c);
        //     if(i == 1) {
        //         elevatorId = commandString[i];
        //     }
        //     else if(i == 3) {
        //         targetFloor = commandString[i];
        //     }
        // }
    }

}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    //TODO: Implement isValidMove
    if(isPass == true || isQuit == true || isSave == true) {
        return true;
    }
    else if((isPickup == true) && (((elevatorId >= 0) && (NUM_ELEVATORS > elevatorId)) && !elevators[elevatorId].isServicing())) {
        return true;
    }
    else if(isPickup == false) {
        if((targetFloor >= 0) && (NUM_FLOORS > targetFloor) && (targetFloor != elevators[elevatorId].getTargetFloor())) {
            return true;
        }
    }
    else
    {
        return false;
    }
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, 
                             const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int diff = 0;
    
    for(int i = 0; i < pickupList.length(); i++) {
        char c = pickupList[i];
        int person = pickupList[i] - '0';
        peopleToPickup[i] = person;
        numPeopleToPickup++;
        

        //take a look at everything below this
        Person p = pickupFloor.getPersonByIndex(i);
        
        totalSatisfaction += (MAX_ANGER - pickupFloor.getPersonByIndex(i).getAngerLevel());
        
        if(currentFloor - targetFloor > diff){
            diff = currentFloor - targetFloor;
            targetFloor = currentFloor;
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
