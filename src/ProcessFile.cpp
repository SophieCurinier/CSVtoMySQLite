#include <dirent.h>
#include <iostream>
#include <functional>
#include "LogFile.cpp"
#include "Time.cpp"

class ProcessFile {
    public: 
        void processFiles(const std::string& dirname, const std::function<void(const std::string&)>& func) {
            LogFile& logFile = LogFile::getInstance();

            DIR* dir = opendir(dirname.c_str());

            if (!dir) {
                logFile.log(Time::getCurrentTime() + " - Erreur lors de l'ouverture du répertoire : " + dirname);
                return;
            }

            struct dirent* entry;

            while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_type == DT_DIR && std::string(entry->d_name) != "." && std::string(entry->d_name) != "..") {
                    std::string subdir = dirname + "/" + entry->d_name;
                    processFiles(subdir, func); // Récursion pour explorer les sous-répertoires
                }
                else if (entry->d_type == DT_REG) {
                    std::string filename = dirname + "/" + entry->d_name;
                    if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".csv") {
                        logFile.log(Time::getCurrentTime() + " - " + filename);
                        func(filename) ;
                    }
                }
            }

            closedir(dir);
        }
};
