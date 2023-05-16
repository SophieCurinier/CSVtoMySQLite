#include <iostream>
#include <thread>
#include "ReadCSV.cpp"
#include "SQLSender.cpp"
#include "ProcessFile.cpp"
#include "LogFile.cpp"
#include "Time.cpp"

using namespace std ;

void removeFile(const string& filename) {
    int result = remove(filename.c_str());
    if (result != 0) {
        // Failed to delete the file
        perror("Error deleting file");
    }
}

void applyCSV(const string& filename, const string& dataBase){
    ReadCSV readCSV ;
    readCSV.fillEventDataFromCSV(filename);
    vector<Event*>* events = readCSV.getEvents();
    SQLSender sqlSender;
    sqlSender.fillDataBase(dataBase,events);
    removeFile(filename);
}

void run(string dataBase, string directory) {
    LogFile& logFile = LogFile::getInstance();
    logFile.openLogFile("/home/swendart/Documents/Dev/CSVtoMySQLite/Ex/logfile.txt");

    ProcessFile p ;
    thread t([&](){
        while (true)
        {
            logFile.log(Time::getCurrentTime() + " - Début du traitement des CSV");
            p.processFiles(directory, bind(applyCSV, placeholders::_1, dataBase));
            logFile.log(Time::getCurrentTime() + " - Fin du traitement des CSV");
            this_thread::sleep_for(chrono::seconds(30));
        }
    });
    t.join();

    logFile.closeLogFile();
}

int main(int argc, char *argv[]) {
    struct {
        string dataBase;
        string directory;
        string logfile ;
        bool isDataBase{false};
        bool isDirectory{false};
    } prog_args;

    for (int i = 1; i < argc; ++i) {
        string arg(argv[i]);    
        if (arg == "--database") {
            prog_args.dataBase = argv[i+1]; i++;
            prog_args.isDataBase = true ;
        } else if (arg == "--directory") {
            prog_args.directory = argv[i+1]; i++;
            prog_args.isDirectory = true ;
        } else if (arg == "--logfile"){
            prog_args.logfile == argv[i+1]; i++;
        } else if ((arg == "-h") || (arg == "--help")) {
            cout << "|| Manual ||" << endl;
            cout << "The program analyzes the set of .csv files contained in the folder and adds the alarms and timers to the sqlite database every 1 hour." << endl;
            cout << "--directory       path of the VLS_TBOX folder" << endl;
            cout << "--database        path of sqlite file with database alarm and chrono" << endl;
            cout << "--logfile         path of logfile" << endl;
        }
    }

    if (prog_args.isDataBase && prog_args.isDirectory){
        run(prog_args.dataBase, prog_args.directory);
    }

    return 0;
}
