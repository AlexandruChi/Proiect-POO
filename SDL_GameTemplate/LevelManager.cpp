#include "LevelManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printError(const char* messege);

unsigned char LevelManager::nrLevels;
unsigned char LevelManager::nrEnmLvl;
size_t LevelManager::nrClcLvl;
int LevelManager::Lvl[20][25];
unsigned char LevelManager::exitLvl[2];
unsigned char LevelManager::playerSpawn[2];
unsigned char(*LevelManager::clcLvl)[3];

ifstream LevelManager::campaine;

void LevelManager::getData(const char* campaineFile) {
    campaine.open(campaineFile);

    if (!campaine.is_open()) {
        string error = "Can not find campaine file: ";
        error += campaineFile;
        printError(error.c_str());
        exit(1);
    }

    streambuf* stream = campaine.rdbuf();
    cin.rdbuf(stream);

    string buffer;

    cin >> buffer;

    if (!strcmp(buffer.c_str(), "nrLevels")) {
        cin >> buffer;
        for (string::iterator i = buffer.begin(); i < buffer.end(); i++) {
            if (!isdigit(*i)) {
                printError("Can not read number of levels");
                exit(1);
            }
        }
        nrLevels = atoi(buffer.c_str());
    } else {
        printError("Campaine file error");
        exit(1);
    }
}

bool LevelManager::readLevel(unsigned char level) {
    if (level > nrLevels) {
        return false;
    }

    string buffer;

    bool foundLevel = false;

    while (cin >> buffer and !foundLevel) {
        if (!strcmp(buffer.c_str(), "lvl")) {
            unsigned char lvl;
            cin >> lvl;
            if (lvl == level) {
                foundLevel = true;
            }
        }
    }

    if (!foundLevel) {
        string error = "Can Not find level ";
        error += to_string(level);
        error += " data";
        printError(error.c_str());
        exit(1);
    }

    bool foundNrEnemy = false;
    bool foundNrClc = false;
    bool foundLvl = false;
    bool foundExitLvl = false;
    bool foundClcLvl = false;
    bool foundPlayerSpawn = false;

    while (cin >> buffer and strcmp(buffer.c_str(), "lvl")) {
        if (!strcmp(buffer.c_str(), "nrEnemy")) {
            cin >> nrEnmLvl;
            foundNrEnemy = true;
        } else if (!strcmp(buffer.c_str(), "nrClc")) {
            cin >> nrClcLvl;
            foundNrClc = true;
        } else if (!strcmp(buffer.c_str(), "map")) {
            for (int i = 0; i < 20; i++) {
                for (int j = 0; i < 25; j++) {
                    cin >> Lvl[i][j];
                }
            }
            foundLvl = true;
        } else if (!strcmp(buffer.c_str(), "exit")) {
            cin >> exitLvl[0] >> exitLvl[1];
            foundExitLvl = true;
        } else if (!strcmp(buffer.c_str(), "clc")) {
            if (foundNrClc) {
                clcLvl = new unsigned char[nrClcLvl][3];
                if (clcLvl == nullptr) {
                    string error = "Can not allocate space for level ";
                    error += to_string(level);
                    printError(error.c_str());
                    exit(1);
                }
                for (int i = 0; i < nrClcLvl; i++) {
                    for (int j = 0; j < 3; j++) {
                        cin >> clcLvl[i][j];
                    }
                }
                foundClcLvl = true;
            }
        } else if (!strcmp(buffer.c_str(), "player")) {
            cin >> playerSpawn[0] >> playerSpawn[1];
            foundPlayerSpawn = true;
        }
    }

    if (!foundNrEnemy or !foundNrClc or !foundLvl or !foundExitLvl or !foundClcLvl or !foundPlayerSpawn) {
        string error = "Can not read data for level ";
        error += to_string(level);
        printError(error.c_str());
        exit(1);
    }

    campaine.clear();
    campaine.seekg(0, std::ios::beg);

    return true;
}

int LevelManager::getNrEnemy() {
    return nrEnmLvl;
}

size_t LevelManager::getNrColectables() {
    return nrClcLvl;
}

int(*LevelManager::getMap())[25] {
    return Lvl;
}

unsigned char(*LevelManager::getExit())[2] {
    return &exitLvl;
}

unsigned char(*LevelManager::getCollectables())[3] {
    return clcLvl;
}

void LevelManager::closeLevelManager() {
    campaine.close();
}
