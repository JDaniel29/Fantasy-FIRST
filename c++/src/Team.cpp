/**
 * 
 * FILE: Team.Cpp
 * DESCRIPTION: This file will be used to manage our
 * linked list of teams. Any functions related to searching
 * for teams and printing information related to them will be here.
 * AUTHOR: Jonathan Daniel
 * 
 * 
 * 
 **/

#include "Team.h"
#include <iostream>

using namespace std;

Team* headNode;
Team* tailNode;

int listSize = 0;

void insertNewTeam(Team* newTeam) {
    if (headNode == 0) {
        headNode = newTeam;
        tailNode = newTeam;

        headNode->setNextTeam(nullptr);
    } else {
        tailNode->setNextTeam(newTeam); //Old tail should print to new team
        tailNode = newTeam;
        tailNode->setNextTeam(nullptr);
    }

    listSize++;
}

void printAllTeams() {
    Team* currentTeam = headNode;
    while (currentTeam != nullptr) {
        currentTeam = currentTeam->getNextTeam();
    }
}

int getTeamPoints(unsigned int teamNum) {
    Team* currentTeam = headNode;
    while (currentTeam != nullptr) {
        if (teamNum == currentTeam->getTeamNum()) {
            return currentTeam->getTotalDistrictPoints();
        }

        currentTeam = currentTeam->getNextTeam();
    }

    cerr << "WARNING: Team " << teamNum << " not found in list" << endl;
    return 0;
}

void removeAllTeams() {
    Team* currentTeam = headNode;
    Team* nextTeam;

    while (currentTeam != nullptr) {
        nextTeam = currentTeam->getNextTeam();
        delete currentTeam;
        currentTeam = nextTeam;
        listSize--;
    }

    headNode = nullptr;
    tailNode = nullptr;
}

int getNumberOfTeamsInList() {
    int metCount = 0;
    
    Team* currentTeam = headNode;
    while (currentTeam != nullptr) {
        currentTeam = currentTeam->getNextTeam();
        metCount++;
    }

    return metCount;
}