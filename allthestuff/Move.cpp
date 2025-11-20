/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * James Lim, Aaron Yoon, Jerry Chen, Milan Charlakolu
 * jblim, aayoon, chjerry, charlakm
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
    elevatorId = -1;
    targetFloor = -1;    
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;

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
        //subtract '0' to rezero char to actual integer
        elevatorId = commandString.at(1) - '0';
    }
    else if (commandString.length() == 4) {
        elevatorId = commandString.at(1) - '0';
        targetFloor = commandString.at(3) - '0';
    }

}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if(isPass == true || isQuit == true || isSave == true) {
        return true;
    }
    else if(((elevatorId >= 0) && (NUM_ELEVATORS > elevatorId)) && !elevators[elevatorId].isServicing()) {
        return true;
    }
    else if((isPickup == false) && (targetFloor >= 0) && (NUM_FLOORS > targetFloor) && (targetFloor != elevators[elevatorId].getTargetFloor())) {
        return true;
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
    int maxDistance = 0;
    int distances[MAX_PEOPLE_PER_FLOOR] = {};
    
    for(int i = 0; i < pickupList.length(); i++) {
        int person = pickupList[i] - '0';
        peopleToPickup[i] = person;
        numPeopleToPickup++;
        
        totalSatisfaction += (MAX_ANGER - pickupFloor.getPersonByIndex(person).getAngerLevel());

        distances[i] = currentFloor - pickupFloor.getPersonByIndex(person).getTargetFloor();
    }
    for (int i = 0; i < sizeof(distances) / sizeof(distances[0]); i++)
    {
        if (abs(distances[i]) > abs(maxDistance))
        {
            maxDistance = distances[i];
        }
    }
    targetFloor = currentFloor - maxDistance;
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
