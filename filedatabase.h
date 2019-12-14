#ifndef FILEDATABASE_H
#define FILEDATABASE_H
#include "main.h"
#include "record.h"

using namespace std;

class fileDatabase
{
public:
    vector<record> dbBuffer;
    string databaseFile;
    bool initialized = 0;

    fileDatabase(string file);
    fileDatabase();

    void openFile(string file);
    vector<unsigned __int64> listRecordedIDs();
    int searchRecord(unsigned __int64 id);
    void editRecordByID(unsigned __int64 id, string firstName = "", string lastName = "", int bal = 0, bool setBal = false);
    void editRecord(int index, string firstName = "", string lastName = "", int bal = 0, bool setBal = false);
    void deleteRecordByID(unsigned __int64 id);
    void deleteRecord(int index);
    void addExistingRecord(record toBeAdded);
    void addRecord(string firstname = "", string lastname = "", int bal = 0);
    void saveDatabase();
private:
    void initializeDatabase();

};

#endif // FILEDATABASE_H
