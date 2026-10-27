/**
 * Filename: fileHandling.c
 * Description: Header file for file loading methods.
 * Author: C. Shannon Terry
 * Date: 10/20/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myVector.h"
#include "management.h"

#define CHARACTER_LIMIT 200
#define VECT_NAME_MAX 20

/*You must gracefully handle a missing (or mistyped) file.
▪ You must gracefully handle a mis-formatted CSV file.
▪ Should you clear vector storage before loading a file or merge the
contents of the file with vectors already in memory, possibly
overwriting some vectors? This is completely up to you in your design*/

int loadFromCSV(char* fileName) {
    FILE* filepointer;
    filepointer = fopen(fileName, "r");
    if (filepointer == NULL) {
        return -1;
    } else {
        char* currentLineText = malloc(sizeof(char) * CHARACTER_LIMIT);
        bool shouldLoopContinue = true;
        if (currentLineText != NULL) {
            do {
                char *newVectName = calloc(VECT_NAME_MAX, sizeof(char));
                if (newVectName == NULL) {
                    return -1; //Failure to allocate memory
                }
                int didItWork = fscanf(filepointer, "%s", currentLineText); //Did the read run properly or hit EOF
                //printf("Scanf obtained: %s\n", currentLineText);
                if (strlen(currentLineText) != 0 && currentLineText[0] != '\r' && currentLineText[0] != '\n' && didItWork == 1) {
                    //Need to check all of these to account for all EOF conditions.
                    vector addVect;
                    char *arg1 = strtok((currentLineText), ",");
                    char *arg2 = NULL;
                    char *arg3 = NULL;
                    char *arg4 = NULL;
                    if (arg1 != NULL) {
                        arg2 = strtok(NULL, ",");
                        arg1[strlen(arg1)] = '\0';
                    }
                    if (arg2 != NULL) {
                        arg3 = strtok(NULL, ",");
                        arg2[strlen(arg2)] = '\0';
                    } 
                    if (arg3 != NULL) {
                        arg4 = strtok(NULL, ",");
                        arg3[strlen(arg3)] = '\0';
                    }
                    if (arg4 != NULL) {
                        arg4[strlen(arg4)] = '\0';
                    }
                    //printf("Args tokenized, but not atof'd.\n");
                    //printf("Arg1: %s Arg 2: %s, Arg 3: %s, Arg 4: %s\n", arg1, arg2, arg3, arg4);
                    if (arg2 != NULL && atof(arg2) != 0) { //Prevent SEGFAULT by checking null first.
                        addVect.x = atof(arg2); 
                    } else {
                        addVect.x = 0;
                    }
                    if (arg3 != NULL && atof(arg3) != 0) {  
                        addVect.y = atof(arg3);
                    } else {
                        addVect.y = 0;
                    }
                    if (arg4 != NULL && atof(arg4) != 0) {  
                        addVect.z = atof(arg4); 
                    } else {
                        addVect.z = 0;
                    }
                    //printf("Tokens obtained properly and x y z assigned.\n");
                    strncpy(newVectName, arg1, VECT_NAME_MAX);
                    strcat(newVectName, "\0");
                    strncpy(addVect.name, newVectName, VECT_NAME_MAX);
                    //printf("Final vect = %s, %f, %f, %f\n", addVect.name, addVect.x, addVect.y, addVect.z);
                    int returnCode = addVector(addVect);
                    if (returnCode == -1) {
                        fclose(filepointer);
                        free(currentLineText);
                        free(newVectName);
                        return -2; //Different error code for a different failure.
                    }
                    free(newVectName);
                } else {
                    shouldLoopContinue = false;
                    free(newVectName);
                }
            } while (shouldLoopContinue);
        } else {
            fclose(filepointer);
            return -2; //Different error code for a different failure.
        }
        free(currentLineText);
        fclose(filepointer);
        return 0;
    }
}

int loadToCSV(char* fileName) {
    FILE* filepointer;
    filepointer = fopen(fileName, "w");
    if (filepointer == NULL) {
        return -1; //File failed to load.
    } else {
        for (int i = 0; i < getVectorCount(); i++) {
            vector currVect = getVectorAtIndex(i);
            if (currVect.name[0] != '\0') { //check for blank vector
                int didItWork = fprintf(filepointer, "%s,%f,%f,%f\n", currVect.name, currVect.x, \
                    currVect.y, currVect.z);
                if (didItWork == -1) { //This means that the write failed.
                    fclose(filepointer);
                    return -2; //Different error code for a different failure.
                }
            }
        }
    }
    fclose(filepointer);
    return 0;
}