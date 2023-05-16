#include <fstream>
#include <vector>
#include "AlarmEvent.cpp"
#include "ChronoEvent.cpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class ReadCSV
{
    private :
        // Attribut
        // vector<Event> eventInCSV;
        vector<Event*> eventInCSV;
        fstream csvFile ;
        bool isAlarmEvent = false;
        bool isChronoEvent = false;

        // Method
        void isAlarmFile(string filePath){
            isAlarmEvent = (filePath.find("alarmes") != string::npos);
        }

        void isChronoFile(string filePath){
            isChronoEvent = (filePath.find("chronologie_digitale") != string::npos);
        }

        void openFile(string filePath){
            try {
                csvFile.open(filePath, ios::in);
            } catch (const std::exception& e) {
                std::cout << e.what() << '\n';
                throw;
            }
        };

        void  readFIle(){
            vector<string> row;
            string line, word, temp;
            if (csvFile.is_open()){
                while (getline(csvFile, line))
                {
                    if (!isEmptyLine(line)){
                        stringstream s(line);
                        while (getline(s, word, ';')) {
                            row.push_back(word);
                        }
                        if (isAlarmEvent && !isChronoEvent){
                            AlarmEvent* alarmEvent = new AlarmEvent(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
                            eventInCSV.push_back(alarmEvent);
                        } else if (!isAlarmEvent && isChronoEvent){
                            ChronoEvent* chronoEvent = new ChronoEvent(row[1], row[2], row[3], row[4]);
                            eventInCSV.push_back(chronoEvent);
                        }
                        row.erase(row.begin(), row.end());
                    }
                }
                
            }
        };

        void closeFile(){
            try{
                csvFile.close();
            } catch (const exception& e) {
                cout << e.what() << '\n';
                throw;
            }
        };

        bool isEmptyFile(){
            string line;
            if (csvFile.is_open()){
                while (std::getline(csvFile, line)) {
                    if (!line.empty()) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool isEmptyLine(string line){
            if (!line.empty() && !(line.size() == 1 && line.size() == 1 && line[0] == '\r') && !(line.size() == 1 && line.size() == 1 && line[0] == '\n')) {
                return false;
            } else {
                return true;
            }
        }
    
    public:
        void fillEventDataFromCSV(string filePath){
            isAlarmFile(filePath);
            isChronoFile(filePath);
            openFile(filePath);
            bool isEmpty = isEmptyFile();
            if (!isEmpty){
                readFIle();
            }
            closeFile();
        };
        vector<Event*>* getEvents(){
            return &eventInCSV;
        }

};