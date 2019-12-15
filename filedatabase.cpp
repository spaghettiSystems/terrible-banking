#include "filedatabase.h"

fileDatabase::fileDatabase(){
    initialized = 0;
}

void fileDatabase::openFile(string file){
    this->dbBuffer.clear();
    this->databaseFile = file;
    ifstream test(file);

    if (test.good()) {
        test.close();
        initialized = 1;
        initializeDatabase();
        return;
    } else {
        test.close();
        ofstream create(file);
        initialized = 1;
        if(!create.is_open()){
            initialized = 0;
        }
        create.close();
        return;
    }
}

void fileDatabase::initializeDatabase() {
    ifstream read(databaseFile);
    string temp;
    record buffer;
    while (getline(read, temp)) {
        buffer.id = stringToInteger(temp);
        getline(read, temp);
        buffer.firstName = temp;
        getline(read, temp);
        buffer.lastName = temp;
        getline(read, temp);
        buffer.balance = stringToInteger(temp);
        dbBuffer.push_back(buffer);
        for (int i = 0; i < 3; i++) {
            read.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void fileDatabase::saveDatabase() {
    ofstream write;
    write.open(databaseFile, ios::trunc);
    if(!write.is_open()){
        return;
    }
    for (record toBeWritten: dbBuffer) {
        write << toBeWritten.id << endl << toBeWritten.firstName << endl << toBeWritten.lastName << endl
              << toBeWritten.balance << endl;
        write << endl << endl << endl;
    }
    write.close();
}

void fileDatabase::addExistingRecord(record toBeAdded) {
    this->dbBuffer.push_back(toBeAdded);
    this->saveDatabase();
}

void fileDatabase::addRecord(string firstname, string lastname, int bal)
{
    record toBeAdded(firstname, lastname, bal);
    this->addExistingRecord(toBeAdded);
}

void fileDatabase::deleteRecord(int index) {
    this->dbBuffer.erase(dbBuffer.begin() + index);
    this->saveDatabase();
}

void fileDatabase::deleteRecordByID(uint64_t id) {
    int index = searchRecord(id);
    if (index < 0){
        return;
    }
    deleteRecord(index);
}

vector<uint64_t> fileDatabase::listRecordedIDs() {
    vector<uint64_t> toBeReturned;
    for (record entry: this->dbBuffer) {
        toBeReturned.push_back(entry.id);
    }
    return toBeReturned;
}

void fileDatabase::editRecord(int index, string firstName, string lastName, int bal, bool setBal){
    if(!firstName.empty()){
        dbBuffer.at(index).firstName = firstName;
    }
    if(!lastName.empty()){
        dbBuffer.at(index).lastName = lastName;
    }
    if(setBal){
        dbBuffer.at(index).balance = bal;
    }
    saveDatabase();
}

void fileDatabase::editRecordByID(uint64_t id, string firstName, string lastName, int bal, bool setBal){
    int index = searchRecord(id);
    if(index < 0){
        return;
    }
    editRecord(index, firstName, lastName, bal, setBal);
}

int fileDatabase::searchRecord(uint64_t id) {
    int left = 0, right = dbBuffer.size(), m;

    while (left < right) {
        m = (left + right) / 2;
        if (dbBuffer[m].id >= id) {
            right = m;
        } else {
            left = m + 1;
        }
    }

    if (dbBuffer[left].id != id) {
        return (left * -1);
    }
    return left;
}

fileDatabase::fileDatabase(string file) {
    this->databaseFile = file;
    ifstream test(file);

    if (test.good()) {
        test.close();
        initialized = 1;
        initializeDatabase();
        return;
    } else {
        test.close();
        ofstream create(file);
        initialized = 1;
        if(create.is_open()){
            initialized = 0;
        }
        create.close();
        return;
    }
}
