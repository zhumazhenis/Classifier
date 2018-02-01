//
// Created by Zhumazhenis on 25/01/2018.
//

#ifndef ASSEMBLERCSA_FUNCTIONS_H
#define ASSEMBLERCSA_FUNCTIONS_H

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <set>
#include <sstream>

using namespace std;

string getMnemonic(ifstream &fptr);

string getOperand(ifstream &fptr);

string normOperand(string operand);

string extract(string s);

bool isOperand(string s);

bool isMnemonic(string s);

bool isAddress(string s);

bool isData(string s);

void toHex(string inFileName);

void process();

#endif //ASSEMBLERCSA_FUNCTIONS_H