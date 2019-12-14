#ifndef RECORD_H
#define RECORD_H
#include "main.h"
using namespace std;

class record
{
public:
    unsigned __int64 id;
    string firstName;
    string lastName;
    int balance;

    record(bool needID = false);
    void generateID();
    record(string fName, string lName, int bal);
};

#endif // RECORD_H
