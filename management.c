/**
 * Filename: management.h
 * Description: Array management method decolaration
 * Author: C. Shannon Terry
 * Date: 9/29/2026
 */

#include "myvector.h"
#include "vectorMethods.h"
#include "management.h"

#define MAX_VECTORS 10

static vector vectorList[MAX_VECTORS];
static int currentEntryCount = 0;

void addVector(vector a) {

}

void removeVector(vector a) {

}

vector getVector(char* name) {

}

bool isArrayFull() {
    if (currentEntryCount == MAX_VECTORS) {
        return true;
    } else {
        return false;
    }
}

void clearArray() {

}
