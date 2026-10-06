/**
 * Filename: vectorMethods.h
 * Description: Vector math implementation.
 * Author: C. Shannon Terry
 * Date: 9/29/2026
 */

#include "myvector.h"
#include "vectorMethods.h"

vector add(vector a, vector b) {
    vector returnVector;
    returnVector.x = a.x + b.x;
    returnVector.y = a.y + b.y;
    returnVector.z = a.z + b.z;
    return returnVector;
}

vector sub(vector a, vector b) {
    vector returnVector;
    returnVector.x = a.x - b.x;
    returnVector.y = a.y - b.y;
    returnVector.z = a.z - b.z;
    return returnVector;
}

vector multiply(vector a, double b) {
    vector returnVector;
    returnVector.x = a.x * b;
    returnVector.y = a.y * b;
    returnVector.z = a.z * b;
    return returnVector;
}

double dotProduct(vector a, vector b) {
    double returnNumber = 0;
    returnNumber = (a.x * b.x) + (a.y * b.y) + (a.z + b.z);
    return returnNumber;
}

vector crossProduct(vector a, vector b) {
    vector returnVector;
    returnVector.x = ((a.y * b.z) - (a.z * b.y));
    returnVector.y = ((a.z * b.x) - (a.x * b.z));
    returnVector.z = ((a.x * b.y) - (a.y * b.x));
    return returnVector;
}