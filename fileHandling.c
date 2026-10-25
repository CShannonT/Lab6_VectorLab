/**
 * Filename: fileHandling.c
 * Description: Header file for file loading methods.
 * Author: C. Shannon Terry
 * Date: 10/20/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myvector.h"
#include "management.h"

#define CHARACTER_LIMIT = 200;

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
        char* currentLineText = malloc(sizeof(char)*CHARACTER_LIMIT);
        if (currentLineText != NULL) {
            //MAKE SURE THAT THIS IS THE CORRECT CHECK
            do {
                fgets(currentLineText, sizeof(currentLineText), filepointer);
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
                vector addVect;
                if (atof(arg2) != 0) {  
                    addVect.x = atof(arg2); //TODO: Check if this needs typechecking.
                } else {
                    addVect.x = 0;
                }
                if (atof(arg3) != 0) {  
                    addVect.y = atof(arg3); //TODO: Check if this needs typechecking.
                } else {
                    addVect.y = 0;
                }
                if (atof(arg4) != 0) {  
                    addVect.z = atof(arg4); //TODO: Check if this needs typechecking.
                } else {
                    addVect.z = 0;
                }
                strcpy(addVect.name, arg1);
                int returnCode = addVector(addVect);
                if (returnCode == -1) {
                    fclose(filepointer);
                    free(currentLineText);
                    return -2; //Different error code for a different failure.
                }
            } while (currentLineText != NULL);
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
        return -1;
    } else {
        /*Find length of vector array by dividing the size of the pointer in
        bytes by the size of the vector. This would still have the issue of
        grabbing blank vectors at the end, but that can be solved a lot more
        easily by adding a check for their blank names.*/
        for (int i = 0; i < (sizeof(vectorList)/sizeof(vector)); i++) {
            vector currVect = getVectorAtIndex(i);
            if (currVect.name[0] != '\0') { //check for blank vector
                int didItWork = fputs("%s,%f,%f,%f\n", currVect.name, currVect.x \
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