#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <sstream>
#include "inttypes.h"
using namespace std;

uint64_t stringToInteger(string x);

class record
{
public:
    uint64_t id;
    string firstName;
    string lastName;
    int balance;

    record(bool needID = false);
    void generateID();
    record(string fName, string lName, int bal);
};

#endif // RECORD_H
