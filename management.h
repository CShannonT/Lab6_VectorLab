/**
 * Filename: management.h
 * Description: Array management method declaration
 * Author: C. Shannon Terry
 * Date: 9/29/2026
 */

#include "myVector.h"

void initializeManagement();
int reallocation();
int addVector(vector a);
int removeVector(vector a);
vector getVector(char* name);
bool doesVectorExist(char* name);
vector getVectorAtIndex(int index);
int getVectorCount();
bool isArrayFull();
void clearArray();
void quitProgram();
void quitProgramCtrlC(int non);