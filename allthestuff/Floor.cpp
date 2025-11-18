/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"
#include <algorithm>

using namespace std;

int Floor::tick(int currentTime) {
	int numExploded = 0;
	std::vector<int> explodedIndices;
    for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++)
	{
		if(people[i].tick(currentTime))
		{
			numExploded++;
			explodedIndices.push_back(i);
		}
	}
	removePeople(explodedIndices.data(), numExploded);
    return numExploded;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople < MAX_PEOPLE_PER_FLOOR)
	{
		people[numPeople] = newPerson;
		numPeople++;
		if (request > 0)
		{
			hasUpRequest = true;
		}
		else if(request < 0)
		{
			hasDownRequest = true;
		}
		
	}
	
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR],
                         int numPeopleToRemove) {
    int toBeRemoved[MAX_PEOPLE_PER_FLOOR] = {};

	//copying const array to sort it
	for (int i = 0; i < numPeopleToRemove; i++)
	{
		toBeRemoved[i] = indicesToRemove[i];
	}

	//from least to greatest
	sort(toBeRemoved, toBeRemoved + numPeopleToRemove);

	//overwrite array values to shift them down mfor each index to be removed
	for(int index : toBeRemoved)
	{
		for (int i = index + 1; i < MAX_PEOPLE_PER_FLOOR; i++)
		{
			people[i] = people[i + 1];
		}
		
	}
	resetRequests();
}

void Floor::resetRequests() {
    for (Person p : people)
	{
		if(p.getCurrentFloor() < p.getTargetFloor())
		{
			hasUpRequest = true;
		}
		else if(p.getCurrentFloor() > p.getTargetFloor())
		{
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
