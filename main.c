/**
 * Filename: main.c
 * Description: Main method. Takes in the text
 * and passes it to control to be parsed.
 * Author: C. Shannon Terry
 * Date: 10/6/2026
 */

#include "management.h"
#include "myVector.h"
#include "control.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARACTER_LIMIT 200

int main(int argc, char* argv[]) {
    int didExitSet = atExit(quitProgram);
    if (didExitSet != 0) {
        printf("The program did not initialize properly. Please try again.\n");
        exit(0);
    } else {
        initializeManagement();
    }
    printf("Welcome to the Vector Calculator!\n");
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0) {
            printf("Functions list:\n");
            printf("Enter a vector name alone to have its data displayed.\n");
            printf("Enter vectors with >vectName = x y z\n");
            printf("You may enter 1 to 3 arguments, but they will be stored as x, y, and z, in that order.\n");
            printf("Add vectors with >vectName1 + vectName2\n");
            printf("Subtract vectors with >vectName1 - vectName2\n");
            printf("Solve for the dot product with >vectName1 * vectName2\n");
            printf("Perform scalar multiplication with >vectName * number\n");
            printf("Obtain a cross product with >vectName1 x vectName2\n");
            printf("You may set a result of these operations (except the dot product) to a new vector by including >vectName = before entering the operation.\n");
            printf("Enter a space between all symbols and values.\n");
            printf("Enter 'list' to get a list of all vectors loaded into memory. You may have a maximum of 10 vectors entered at once.\n");
            printf("Enter 'clear' to clear the currently entered vectors from memory.\n");
            printf("Enter 'quit' to exit the program.\n");
        }
    }
    int returnVal = 1;
    char userInput[CHARACTER_LIMIT];
    while (returnVal != 0) {
        printf("VectorCalc> ");
        fgets(userInput, sizeof(userInput), stdin);
        userInput[strlen(userInput)-1] = ' '; //Replace the newline/CR control character from the user's enter.
        returnVal = parseInput(userInput);
    }
    printf("Quitting program...\n");
    return 0;
}