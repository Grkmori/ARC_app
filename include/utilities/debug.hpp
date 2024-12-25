
#pragma once

#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


class Debug {
private:


public:
    /* FUNCTIONS - JSON */
    /* Output a .json file */
    void logJsonToFile(const string& logFile, const json& jsonObject) {
        ofstream logStream(logFile, ios::app);
        if (!logStream) {
            cerr << "Error opening log file!" << endl;
            return;
        }

        logStream << jsonObject.dump(2) << endl;
        logStream.close();
    }

    /* Output to console */
    void logJsonToConsole(const json& jsonObject) {
        cout << jsonObject.dump(2) << endl;
    }
};
