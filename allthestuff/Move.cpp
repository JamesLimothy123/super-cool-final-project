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

Move::Move(string commandString) {
    // Initialize defaults
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;

    // Empty string -> Pass move
    if (commandString.size() == 0) {
        isPass = true;
        return;
    }

    char c0 = commandString[0];

    if (c0 == 's' || c0 == 'S') {
        isSave = true;
        return;
    }
    if (c0 == 'q' || c0 == 'Q') {
        isQuit = true;
        return;
    }

    if (c0 != 'e' && c0 != 'E') {
        return;
    }

    if (commandString.size() == 3 &&
        isdigit(commandString[1]) &&
        (commandString[2] == 'p' || commandString[2] == 'P')) {

        isPickup = true;
        elevatorId = commandString[1] - '0';
        return;
    }

    if (commandString.size() == 4 &&
        isdigit(commandString[1]) &&
        (commandString[2] == 'f' || commandString[2] == 'F') &&
        isdigit(commandString[3])) {

        elevatorId = commandString[1] - '0';
        targetFloor = commandString[3] - '0';
        return;
    }

}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPass || isSave || isQuit) {
        return true;
    }

    if (elevatorId < 0 || elevatorId >= NUM_ELEVATORS) {
        return false;
    }

    if (elevators[elevatorId].isServicing()) {
        return false;
    }

    if (isPickup) {
        return true;
    }

    if (targetFloor < 0 || targetFloor >= NUM_FLOORS) {
        return false;
    }

    if (targetFloor == elevators[elevatorId].getCurrentFloor()) {
        return false;
    }

    return true;
}

void Move::setPeopleToPickup(const string& pickupList,
                             const int currentFloor,
                             const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;

    int maxDistance = 0;
    bool first = true;

    for (int i = 0; i < static_cast<int>(pickupList.size()); ++i) {
        int idx = pickupList[i] - '0';

        peopleToPickup[numPeopleToPickup] = idx;
        numPeopleToPickup++;

        Person p = pickupFloor.getPersonByIndex(idx);

        totalSatisfaction += (MAX_ANGER - p.getAngerLevel());

        int distance = currentFloor - p.getTargetFloor();

        if (first || std::abs(distance) > std::abs(maxDistance)) {
            maxDistance = distance;
            first = false;
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
