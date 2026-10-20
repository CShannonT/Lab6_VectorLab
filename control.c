/**
 * Filename: control.h
 * Description: Main method that handles typed arguments
 * Author: C. Shannon Terry
 * Date: 10/6/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "management.h"
#include "vectorMethods.h"
#include "myVector.h"
#include "control.h"

#define MAX_VECTORS 10 
#define NAMELENGTH 20
#define TERMINATOR '\0'

int parseInput(char *inputText) {
    //printf("ParseInput begins.\n");
    //printf("Input is %s\n", inputText);
    char *arg1 = strtok((inputText), " ");
    char *arg2 = NULL;
    char *arg3 = NULL;
    char *arg4 = NULL;
    char *arg5 = NULL;
    char *newVectName = calloc(strlen(arg1), sizeof(char));
    if (arg1 != NULL) {
        arg2 = strtok(NULL, " ");
        arg1[strlen(arg1)] = '\0';
    }
    if (arg2 != NULL) {
        arg3 = strtok(NULL, " ");
        arg2[strlen(arg2)] = '\0';
    } 
    if (arg3 != NULL) {
        arg4 = strtok(NULL, " ");
        arg3[strlen(arg3)] = '\0';
    }
    if (arg4 != NULL) {
        arg5 = strtok(NULL, " ");
        arg4[strlen(arg4)] = '\0';
    }
    if (arg5 != NULL) {
        arg5[strlen(arg5)] = '\0';
    }
    //printf("arg1: %s\narg2: %s\narg3: %s\narg4: %s\narg5: %s\n", arg1, arg2, arg3, arg4, arg5);
    if (!arg2) { //One argument. Likely EXIT, CLEAR, or LIST
        if (strcmp(arg1, "quit") == 0) {
            return 0; //0 will be used as an exit command in main.
        } else if (strcmp(arg1, "clear") == 0) {
            clearArray();
            printf("All vectors cleared.\n");
        } else if (strcmp(arg1, "list") == 0) {
            printf("Vectors in memory:\n");
            for (int i = 0; i < MAX_VECTORS; i++) {
                vector indVect = getVectorAtIndex(i);
                if (!(indVect.name[0] == TERMINATOR)) {
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        indVect.name, indVect.x, indVect.y, indVect.z);
                } //This avoids printing blank vectors.
            } 
        } else { //Final single arg case is a single variable name; SOMETHING WRONG HERE THAT SEGFAULTS
            if (doesVectorExist(arg1)) {
                vector vectArg = getVector(arg1);
                if (!(vectArg.name[0] == TERMINATOR)) {
                        printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectArg.name, vectArg.x, vectArg.y, vectArg.z);
                } else {
                    printf("No vector of name %s found.\n", arg1);
                }
            } else {
                printf("No vector of name %s found.\n", arg1);
            }
        }
    } else if (!arg3) { //There are actually no two arg commands.
        printf("Error. Command not recognized. Please enter a valid command.\n");
    } else if (!arg4) { //There are a few options here. 
        //printf("Reached !arg4 branch.\n");
        if (strcmp(arg2, "+") == 0) { //Addition
            vector vectA = getVector(arg1);
            vector vectB = getVector(arg3);
            if ((doesVectorExist(vectA.name)) && doesVectorExist(vectB.name)) {
                if ((!(vectA.name[0] == TERMINATOR)) && (!(vectB.name[0] == TERMINATOR))) {
                    //If both vectors are valid:
                    vector result = add(vectA, vectB);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectA.x, vectA.y, vectA.z);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectB.name, vectB.x, vectB.y, vectB.z);
                    printf("%s + %s = (%.2f + %.2f, %.2f + %.2f, %.2f + %.2f) = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectB.name, \
                        vectA.x, vectB.x, \
                        vectA.y, vectB.y, \
                        vectA.z, vectB.z, \
                        result.x, result.y, result.z);
                } else {
                    printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                }
            } else {
                printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
            }
        } else if (strcmp(arg2, "-") == 0) { //Subtraction
            vector vectA = getVector(arg1);
            vector vectB = getVector(arg3);
            if ((doesVectorExist(vectA.name)) && doesVectorExist(vectB.name)) {
                if (!(vectA.name[0] == TERMINATOR) && (!(vectB.name[0] == TERMINATOR))) {
                    //If both vectors are valid:
                    vector result = subtract(vectA, vectB);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectA.x, vectA.y, vectA.z);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectB.name, vectB.x, vectB.y, vectB.z);
                    printf("%s - %s = (%.2f - %.2f, %.2f - %.2f, %.2f - %.2f) = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectB.name, \
                        vectA.x, vectB.x, \
                        vectA.y, vectB.y, \
                        vectA.z, vectB.z, \
                        result.x, result.y, result.z);
                } else {
                    printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                }
            } else {
                printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
            }
        } else if (strcmp(arg2, "*") == 0) { //Dot Product OR Scalar Multiplication
            //Need to check for scalar multiplication.
            double scalarVal1 = atof(arg1); //Check to make sure these can parse ints. That
            double scalarVal2 = atof(arg3); //or add to the help that they always need to be floats.
            vector vectA = getVector(arg1);
            vector vectB = getVector(arg3);
            if ((scalarVal1 == 0) && (scalarVal2 == 0)) { //atof returns 0 on a failure to find digits.
                    //Vector times vector - Dot product
                if ((doesVectorExist(vectA.name)) && doesVectorExist(vectB.name)) {
                    if (!(vectA.name[0] == TERMINATOR) && (!(vectB.name[0] == TERMINATOR))) {
                    //If both vectors are valid:
                    double result = dotProduct(vectA, vectB);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectA.x, vectA.y, vectA.z);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectB.name, vectB.x, vectB.y, vectB.z);
                    printf("%s * %s = (%.2f * %.2f + %.2f * %.2f + %.2f * %.2f) = %.2f\n", \
                        vectA.name, vectB.name, \
                        vectA.x, vectB.x, \
                        vectA.y, vectB.y, \
                        vectA.z, vectB.z, \
                        result);
                    } else {
                        printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                    }
                } else {
                    printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                }
            } else if ((scalarVal1 != 0) && (scalarVal2 == 0)) { 
                //Scalar times vector
                if (doesVectorExist(vectB.name)) {
                    if (!(vectB.name[0] == TERMINATOR)) {
                        //If the vector is valid:
                        vector result = multiply(vectB, scalarVal1);
                        printf("%s = (%.2f, %.2f, %.2f)\n", \
                            vectB.name, vectB.x, vectB.y, vectB.z);
                        printf("%s * %.2f = (%.2f * %.2f, %.2f * %.2f, %.2f * %.2f) = (%.2f, %.2f, %.2f)\n", \
                            vectB.name, scalarVal1, \
                            vectB.x, scalarVal1, \
                            vectB.y, scalarVal1, \
                            vectB.z, scalarVal1, \
                            result.x, result.y, result.z);
                    } else {
                        printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                    }
                }
            } else if ((scalarVal1 == 0) && (scalarVal2 != 0)) {
                //Vector times scalar
                if (doesVectorExist(vectA.name)) {
                    if (!(vectA.name[0] == TERMINATOR)) {
                        //If the vector is valid:
                        vector result = multiply(vectA, scalarVal2);
                        result.x = vectA.x * scalarVal2;
                        result.y = vectA.y * scalarVal2;
                        result.z = vectA.z * scalarVal2;
                        printf("%s = (%.2f, %.2f, %.2f)\n", \
                            vectA.name, vectA.x, vectA.y, vectA.z);
                        printf("%s * %.2f = (%.2f * %.2f, %.2f * %.2f, %.2f * %.2f) = (%.2f, %.2f, %.2f)\n", \
                            vectA.name, scalarVal2, \
                            vectA.x, scalarVal2, \
                            vectA.y, scalarVal2, \
                            vectA.z, scalarVal2, \
                            result.x, result.y, result.z);
                    } else {
                        printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                    }
                }
            } else { //Error case
                printf("Error. One or more arguments are invalid. Use the -h command line option to see commands and formatting.\n");
            }
        } else if ((strcmp(arg2, "x") == 0)) { //Cross Product
            vector vectA = getVector(arg1);
            vector vectB = getVector(arg3);
            if ((doesVectorExist(vectA.name)) && doesVectorExist(vectB.name)) {
                if ((!(vectA.name[0] == TERMINATOR)) && (!(vectB.name[0] == TERMINATOR))) {
                    //If both vectors are valid:
                    vector result = crossProduct(vectA, vectB);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectA.x, vectA.y, vectA.z);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectB.name, vectB.x, vectB.y, vectB.z);
                    printf("%s x %s = (%.2f * %.2f - %.2f * %.2f, %.2f * %.2f - %.2f * %.2f, %.2f * %.2f - %.2f * %.2f) = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectB.name, \
                        vectA.y, vectB.z, vectA.z, vectB.y, \
                        vectA.z, vectB.x, vectA.x, vectB.z, \
                        vectA.x, vectB.y, vectA.y, vectB.x, \
                        result.x, result.y, result.z);
                } 
            }
        } else if ((strcmp(arg2, "=") == 0)) { //Vector creation - only X input.
            if (!(arg1[0] == TERMINATOR)) { 
                //As long as a name is entered, you can use it for a vector.
                vector addVect;
                if (atof(arg3) != 0) {  
                    addVect.x = atof(arg3); //TODO: Check if this needs typechecking.
                } else {
                    addVect.x = 0;
                }
                strcpy(addVect.name, arg1);
                addVector(addVect);
            } else {
                printf("To initialize a vector, specify the name first, \
                        followed by an equal sign, followed by a decimal number.\n");
            }
        } else {
            printf("Error. One or more arguments are invalid. Use the -h command line option to see commands and formatting.\n");
        }
    } else if (!arg5) { //The only four arg inputs are two value vector entries.
        //printf("Reached !arg5 branch.\n");
        if (!(arg1[0] == TERMINATOR)) { 
            //As long as a name is entered, you can use it for a vector.
            if ((strcmp(arg2, "=") == 0)) {
                vector addVect;
                if (atof(arg3) != 0) {  
                    addVect.x = atof(arg3); //TODO: Check if this needs typechecking.
                } else {
                    addVect.x = 0;
                }
                if (atof(arg4) != 0) {  
                    addVect.y = atof(arg4); //TODO: Check if this needs typechecking.
                } else {
                    addVect.y = 0;
                }
                strcpy(addVect.name, arg1);
                int returnCode = addVector(addVect);
                if (returnCode == -1) {
                    printf("Vector add failed. Please clear memory to make space.\n");
                }
            } else {
                printf("Error. One or more arguments are invalid. Use the -h command line option to see commands and formatting.\n");
            }
        } else {
            printf("Error. One or more arguments are invalid. Use the -h command line option to see commands and formatting.\n");
        }
    } else { //Final set. 5 argument inputs have many options.
        //printf("Reached 5 argument branch.\n");
        if (strcmp(arg4, "+") == 0) { //Addition
            //printf("Reached 5 argument branch - adding.\n");
            strncpy(newVectName, arg1, NAMELENGTH); //SEGFAULT BETWEEN THESE TWO PRINTS
            vector vectA = getVector(arg3);
            vector vectB = getVector(arg5);
            if ((doesVectorExist(vectA.name)) && doesVectorExist(vectB.name)) {
                if ((!(vectA.name[0] == TERMINATOR)) && (!(vectB.name[0] == TERMINATOR))) {
                    //If both vectors are valid:
                    vector result = add(vectA, vectB);
                    strcpy(result.name, newVectName);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectA.x, vectA.y, vectA.z);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectB.name, vectB.x, vectB.y, vectB.z);
                    printf("%s + %s = (%.2f + %.2f, %.2f + %.2f, %.2f + %.2f) = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectB.name, \
                        vectA.x, vectB.x, \
                        vectA.y, vectB.y, \
                        vectA.z, vectB.z, \
                        result.x, result.y, result.z);
                    int returnCode = addVector(result);
                    if (returnCode == -1) {
                        printf("Vector add failed. Please clear memory to make space.\n");
                    }
                } else {
                    printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                }
            } else {
                printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
            }
        } else if (strcmp(arg4, "-") == 0) { //Subtraction
            strcpy(newVectName, arg1);
            vector vectA = getVector(arg3);
            vector vectB = getVector(arg5);
            if ((doesVectorExist(vectA.name)) && doesVectorExist(vectB.name)) {
                if ((!(vectA.name[0] == TERMINATOR)) && (!(vectB.name[0] == TERMINATOR))) {
                    //If both vectors are valid:
                    vector result = subtract(vectA, vectB);
                    strcpy(result.name, newVectName);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectA.x, vectA.y, vectA.z);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectB.name, vectB.x, vectB.y, vectB.z);
                    printf("%s - %s = (%.2f - %.2f, %.2f - %.2f, %.2f - %.2f) = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectB.name, \
                        vectA.x, vectB.x, \
                        vectA.y, vectB.y, \
                        vectA.z, vectB.z, \
                        result.x, result.y, result.z);
                    int returnCode = addVector(result);
                    if (returnCode == -1) {
                        printf("Vector add failed. Please clear memory to make space.\n");
                    }
                } else {
                    printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                }
            } else {
                printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
            }
        } else if (strcmp(arg4, "*") == 0) { //Only Scalar multiplication with assignment to a new vector can occur.
            strcpy(newVectName, arg1);
            double scalarVal1 = atof(arg3); //TODO: Check to make sure these can parse ints. That
            double scalarVal2 = atof(arg5); //or add to the help that they always need to be floats.
            vector vectA = getVector(arg3);
            vector vectB = getVector(arg5);
            if ((scalarVal1 != 0) && (scalarVal2 == 0)) { 
                //Scalar times vector
                if (doesVectorExist(vectB.name)) {
                    if (!(vectB.name[0] == TERMINATOR)) {
                    //If the vector is valid:
                        vector result = multiply(vectB, scalarVal1);
                        strcpy(result.name, newVectName);
                        printf("%s = (%.2f, %.2f, %.2f)\n", \
                            vectB.name, vectB.x, vectB.y, vectB.z);
                        printf("%s * %.2f = (%.2f * %.2f, %.2f * %.2f, %.2f * %.2f) = (%.2f, %.2f, %.2f)\n", \
                            vectB.name, scalarVal1, \
                            vectB.x, scalarVal1, \
                            vectB.y, scalarVal1, \
                            vectB.z, scalarVal1, \
                            result.x, result.y, result.z);
                        int returnCode = addVector(result);
                        if (returnCode == -1) {
                            printf("Vector add failed. Please clear memory to make space.\n");
                        }
                    } else {
                        printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                    }
                } else {
                    printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                }
            } else if ((scalarVal1 == 0) && (scalarVal2 != 0)) {
                //Vector times scalar
                if ((doesVectorExist(vectA.name))) {
                    if (!(vectA.name[0] == TERMINATOR)) {
                        //If the vector is valid:
                        vector result = multiply(vectA, scalarVal2);
                        strcpy(result.name, newVectName);
                        result.x = vectA.x * scalarVal2;
                        result.y = vectA.y * scalarVal2;
                        result.z = vectA.z * scalarVal2;
                        printf("%s = (%.2f, %.2f, %.2f)\n", \
                            vectA.name, vectA.x, vectA.y, vectA.z);
                        printf("%s * %.2f = (%.2f * %.2f, %.2f * %.2f, %.2f * %.2f) = (%.2f, %.2f, %.2f)\n", \
                            vectA.name, scalarVal2, \
                            vectA.x, scalarVal2, \
                            vectA.y, scalarVal2, \
                            vectA.z, scalarVal2, \
                            result.x, result.y, result.z);
                        int returnCode = addVector(result);
                        if (returnCode == -1) {
                            printf("Vector add failed. Please clear memory to make space.\n");
                        }
                    } else {
                        printf("Error. One or more vector names are invalid. Please enter a valid name.\n");
                    }
                } else { //Error case
                    printf("Error. One or more arguments are invalid. Use the -h command line option to see commands and formatting.\n");
                }
            } else { //Error case
                printf("Error. Vector dot product cannot be stored as a vector, as it is a scalar value.\n");
            }
        } else if ((strcmp(arg4, "x") == 0)) { //Cross Product
            strcpy(newVectName, arg1);
            vector vectA = getVector(arg3);
            vector vectB = getVector(arg5);
            if ((doesVectorExist(vectA.name)) && doesVectorExist(vectB.name)) {
                if ((!(vectA.name[0] == TERMINATOR)) && (!(vectB.name[0] == TERMINATOR))) {
                    //If both vectors are valid:
                    vector result = crossProduct(vectA, vectB);
                    strcpy(result.name, newVectName);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectA.x, vectA.y, vectA.z);
                    printf("%s = (%.2f, %.2f, %.2f)\n", \
                        vectB.name, vectB.x, vectB.y, vectB.z);
                    printf("%s x %s = (%.2f * %.2f - %.2f * %.2f, %.2f * %.2f - %.2f * %.2f, %.2f * %.2f - %.2f * %.2f) = (%.2f, %.2f, %.2f)\n", \
                        vectA.name, vectB.name, \
                        vectA.y, vectB.z, vectA.z, vectB.y, \
                        vectA.z, vectB.x, vectA.x, vectB.z, \
                        vectA.x, vectB.y, vectA.y, vectB.x, \
                        result.x, result.y, result.z);
                    int returnCode = addVector(result);
                    if (returnCode == -1) {
                        printf("Vector add failed. Please clear memory to make space.\n");
                    }
                } else {
                    printf("Error. One or more arguments are invalid. Use the -h command line option to see commands and formatting.\n");
                }
            } else {
                printf("Error. One or more arguments are invalid. Use the -h command line option to see commands and formatting.\n");
            }
        } else if (!(arg1[0] == TERMINATOR)) { 
            //As long as a name is entered, you can use it for a vector.
            //printf("Reached entering vector branch.\n");
            if ((strcmp(arg2, "=") == 0)) {
                vector addVect;
                if (atof(arg3) != 0) {  
                    addVect.x = atof(arg3); //TODO: Check if this needs typechecking.
                } else {
                    addVect.x = 0;
                }
                if (atof(arg4) != 0) {  
                    addVect.y = atof(arg4); //TODO: Check if this needs typechecking.
                } else {
                    addVect.y = 0;
                }
                if (atof(arg5) != 0) {  
                    addVect.z = atof(arg5); //TODO: Check if this needs typechecking.
                } else {
                    addVect.z = 0;
                }
                strcpy(addVect.name, arg1);
                int returnCode = addVector(addVect);
                if (returnCode == -1) {
                    printf("Vector add failed. Please clear memory to make space.\n");
                }
            } else {
                printf("Error. One or more arguments are invalid. Use the -h command line option to see commands and formatting.\n");
            }  //Finally done!
        } else {
            printf("No valid arguments provided.\n");
        }
    }
    printf("Operation complete.\n");
    free(newVectName);
    return 1;
}