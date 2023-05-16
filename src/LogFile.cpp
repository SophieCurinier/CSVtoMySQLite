#pragma once
#include <iostream>
#include <fstream>

using namespace std ;

class LogFile 
{
    ofstream logFile;
    LogFile(){};

    public :
        static LogFile& getInstance() {
            static LogFile instance;
            return instance;
        }

        void openLogFile(const string& filename) {
            logFile.open(filename, ios::app);
        }

        void closeLogFile() {
            if (logFile.is_open()) {
                logFile.close();
            }
        }

        void log(const string& message) {
            if (logFile.is_open()) {
                logFile << message << endl;
                cout << message << endl;
            }
        }
};
