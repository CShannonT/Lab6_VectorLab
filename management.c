/**
 * Filename: management.h
 * Description: Array management method decolaration
 * Author: C. Shannon Terry
 * Date: 9/29/2026
 */

#include "myVector.h"
#include "vectorMethods.h"
#include "management.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TERMINATOR '\0'
static vector *vectorList;
static int currentEntryCount = 0;
static int currentMax = 1;

void initializeManagement() {
    vectorList = calloc(sizeof(vector), sizeof(vector));
    vector blank;
    strcpy(blank.name, "\0");
    blank.x = 0;
    blank.y = 0;
    blank.z = 0;
    vectorList[0] = blank;
}

int reallocation() {
    currentMax *= 2; //Increase max size.
    vector blank;
    strcpy(blank.name, "\0");
    //printf("Curr max is %d\n", currentMax);
    blank.x = 0;
    blank.y = 0;
    blank.z = 0;
    vector *tempPointer = realloc(vectorList, (sizeof(vector)*currentMax));
    if (tempPointer != NULL) {
        vectorList = tempPointer;
        for (int i = currentEntryCount; i < currentMax; i++) {
            vectorList[i] = blank; //Fill empty positions with blank vectors
            //Needed to avoid undefined accesses to garbage data in file IO.
        }
        return 0;
    } else {
        return -1; //Failed to allocate memory
    }
}

/**
 * Returns 0 on success, or -1 on failure.
 */
int addVector(vector a) {
    if (!isArrayFull()) {
        int i = 0;
        bool added = false;
        while (!added) {
            vector currentVector = vectorList[i];
            //If the name of the vector at i is blank, it is a usable spot.
            if ((strcmp(currentVector.name, a.name)) == 0) { 
                //Same name means same vector, leading to reassignment.
                vectorList[i] = a;
                added = true;
            } else if (currentVector.name[0] == TERMINATOR) {
                vectorList[i] = a;
                added = true;
                currentEntryCount++;
            } else {
                i++;
            }
        }
        return 0;
    } else {
        int retCode = reallocation();
        if (retCode == 0) {
            return addVector(a); //This could be a really bad idea.
            //It seems to have worked fine though.
        } else {
            printf("Memory reallocation failed.\n");
            return -1; //Failure to add.
        }
    }
    return -1;
}

/**
 * Returns 0 on success, or -1 on failure.
 */
int removeVector(vector a) {
    vector blank;
    strcpy(blank.name, "\0");
    blank.x = 0;
    blank.y = 0;
    blank.z = 0;
    int i = 0;
    bool removed = false; 
    while ((!removed) && (i < currentMax)) {
        vector currentVector = vectorList[i];
        if ((strcmp(currentVector.name, a.name)) == 0) {
            vectorList[i] = blank;
            removed = true;
            currentEntryCount--;
        } else {
            i++;
        }
    }
    if (i < currentMax) {
        return 0;
    } else {
        return -1; //Failure to remove - does not exist.
    }
}

vector getVector(char* name) {
    vector returnVector;
    vector blank;
    strcpy(blank.name, "\0");
    blank.x = 0;
    blank.y = 0;
    blank.z = 0;
    int i = 0;
    bool found = false; 
    while ((!found) && (i < currentMax)) {
        vector currentVector = vectorList[i];
        if ((strcmp(currentVector.name, name)) == 0) {
            returnVector = vectorList[i];
            found = true;
        } else {
            i++;
        }
    }
    if (found) {
        return returnVector;
    } else {
        return blank;
    }
}

bool doesVectorExist(char* name) {
    int i = 0;
    bool found = false; 
    while ((!found) &&  (i < currentMax)) {
        vector currentVector = vectorList[i];
        if ((strcmp(currentVector.name, name)) == 0) {
            found = true;
        } else {
            i++;
        }
    }
    return found;
}

vector getVectorAtIndex(int index) {
    vector returnVector = vectorList[index];
    return returnVector;
    //When a vector is returned in this way, its name will be blank
    //if there is no vector at that position.
}

int getVectorCount() {
    return currentEntryCount;
}

bool isArrayFull() {
    if (currentEntryCount >= currentMax) {
        return true;
    } else {
        return false;
    }
}

void clearArray() {
    vector blank;
    strcpy(blank.name, "\0");
    blank.x = 0;
    blank.y = 0;
    blank.z = 0;
    for (int i = 0; i < currentMax; i++) {
        vectorList[i] = blank;
    }
    free(vectorList);
    initializeManagement();
    currentEntryCount = 0;
}

void quitProgram() {
    free(vectorList);
    exit(0);
}
