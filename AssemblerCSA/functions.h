//
// Created by Zhumazhenis on 03/03/2018.
//

#ifndef ASSEMBLERCSA2_FUNCTIONS_H
#define ASSEMBLERCSA2_FUNCTIONS_H

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <iomanip>

using namespace std;

typedef pair<int, int> mp; // making pair function

char *getHex(ifstream &fptr); // Task 1: reads from .hex files and

void testGetHex(); // Task 1: Tests

char alu(char a, char b, char op); // Task 2: alu function for arithmetic operations

void testAlu(); // Task 2: Tests

void updatePC(int offset); // Task 3: updates pc counter according to table in Assignment 1

void testTask34(); // Task 3, 4: Tests

void finalFunction();

ifstream buildFile(); // makes iftream object to read from file


#endif //ASSEMBLERCSA2_FUNCTIONS_H
