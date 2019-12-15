#include "record.h"

uint64_t stringToInteger(string x) {
    uint64_t temp;
    stringstream epic(x);
    epic >> temp;
    return temp;
}

void record::generateID() {
    this->id = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();
}

record::record(bool needID) {
    if (needID) {
        generateID();
    }
    return;
}

record::record(string fName, string lName, int bal) {
    this->firstName = fName;
    this->lastName = lName;
    this->balance = bal;
    generateID();
    return;
}
