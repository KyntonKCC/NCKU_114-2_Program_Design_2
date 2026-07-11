#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// 0x00F0 equals bits 4-7 which is location code
const unsigned short MASK_LOC = 0x00F0; 

struct Cat {
    int id;
    char name[20];
    double weight;
    unsigned short status; 
};

// ================== modify area ==================

// calculate info and add new cat
void addCat(ifstream &inputFile, fstream &dbFile) {
    Cat newCat;
    unsigned int highByte, lowByte;
    inputFile >> newCat.name >> newCat.weight >> hex >> highByte >> lowByte;
    inputFile >> dec; 
    dbFile.clear();
    dbFile.seekg(0, ios::end);
    long long fileSize = dbFile.tellg();
    newCat.id = (fileSize / sizeof(Cat)) + 1;
    newCat.status = (highByte << 8) | lowByte;
    dbFile.seekp(0, ios::end);
    dbFile.write(reinterpret_cast<char*>(&newCat), sizeof(Cat));
}

// use random access to get the record and update location
void updateLocation(ifstream &inputFile, fstream &dbFile) {
    // use (& ~MASK_LOC) clear location bits
    // use | set new location
    int targetId, newLocCode;
    inputFile >> targetId >> newLocCode;
    long long offset = (long long)(targetId - 1) * sizeof(Cat);
    dbFile.clear();
    dbFile.seekg(0, ios::end);
    long long fileSize = dbFile.tellg();
    if (offset < 0 || offset >= fileSize) {
        cout << "Error: ID " << targetId << " out of range" << endl;
        return;
    }
    Cat cat;
    dbFile.seekg(offset, ios::beg);
    dbFile.read(reinterpret_cast<char*>(&cat), sizeof(Cat));
    cat.status = (cat.status & ~MASK_LOC) | ((newLocCode << 4) & MASK_LOC);
    dbFile.seekp(offset, ios::beg);
    dbFile.write(reinterpret_cast<char*>(&cat), sizeof(Cat));
}

// search and list cats at the location
void searchByLoc(ifstream &inputFile, fstream &dbFile) {
    // use (status & MASK_LOC) >> 4 to get location code
    int searchLoc;
    inputFile >> searchLoc;
    cout << "--- Location " << searchLoc << " Search Results ---" << endl;
    dbFile.clear();
    dbFile.seekg(0, ios::end);
    long long fileSize = dbFile.tellg();
    int totalCats = fileSize / sizeof(Cat);
    dbFile.seekg(0, ios::beg);
    for (int i = 0; i < totalCats; ++i) {
        Cat cat;
        dbFile.read(reinterpret_cast<char*>(&cat), sizeof(Cat));
        int currentLoc = (cat.status & MASK_LOC) >> 4;
        if (currentLoc == searchLoc) {
            cout << "ID: 0x" << hex << cat.id << dec << " | Name: " << cat.name << endl;
        }
    }
}

int main() {
    // open file, read input file and call corresponding function
    ifstream inputFile;
    inputFile.open("input.txt");
    if (!inputFile) return 0;
    fstream dbFile("cat.dat", ios::in | ios::out | ios::binary | ios::trunc);
    if (!dbFile) return 0;
    int command;
    while (inputFile >> command) {
        if (command == 1) {
            addCat(inputFile, dbFile);
        } 
        else if (command == 2) {
            updateLocation(inputFile, dbFile);
        } 
        else if (command == 3) {
            searchByLoc(inputFile, dbFile);
        } 
        else if (command == 4) {
            break;
        } 
        else if (command == 5) {
            dbFile.clear();
            dbFile.seekg(0, ios::end);
            long long size = dbFile.tellg();
            cout << "Current File Size: " << size << " bytes" << endl;
        }
    }
    inputFile.close();
    dbFile.close();
    // close file
    return 0;
}

// ================== modify area ==================
