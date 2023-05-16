#include <iostream>
#include <thread>
#include "ReadCSV.cpp"
#include "SQLSender.cpp"
#include "ProcessFile.cpp"

void removeFile(const std::string& filename) {
    int result = std::remove(filename.c_str());
    if (result != 0) {
        // Failed to delete the file
        perror("Error deleting file");
    }
}

void applyCSV(const std::string& filename){
    ReadCSV readCSV ;
    readCSV.fillEventDataFromCSV(filename);
    vector<Event*>* events = readCSV.getEvents();
    SQLSender sqlSender;
    sqlSender.fillDataBase("/home/swendart/Documents/Dev/CSVtoMySQLite/sqlite/vals.db",events);
    removeFile(filename);
}

int main(int, char**) {
    // Apply same for all file in following directory
    ProcessFile p ;
    std::thread t([&](){
        while (true)
        {
            std::cout << "Traitement des CSV" << std::endl;
            p.processFiles("/home/swendart/Documents/Dev/CSVtoMySQLite/Ex/Test/", applyCSV);
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
        
    });
    t.join();
    return 0;
}
