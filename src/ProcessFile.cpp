#include <dirent.h>
#include <iostream>
#include <functional>
#include "LogFile.cpp"
#include "Time.cpp"

using namespace std;

class ProcessFile {
    public: 
        void processFiles(const string& dirname, const function<void(const string&)>& func) {
            DIR* dir = opendir(dirname.c_str());

            if (!dir) {
                LogFile::instance()->log(Time::getCurrentTime() + " - Erreur lors de l'ouverture du répertoire : " + dirname);
                return;
            }

            struct dirent* entry;

            while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_type == DT_DIR && string(entry->d_name) != "." && string(entry->d_name) != "..") {
                    string subdir = dirname + "/" + entry->d_name;
                    processFiles(subdir, func);
                }
                else if (entry->d_type == DT_REG) {
                    string filename = dirname + "/" + entry->d_name;
                    if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".csv") {
                        LogFile::instance()->log(Time::getCurrentTime() + " - " + filename);
                        func(filename) ;
                    }
                }
            }

            closedir(dir);
        }
};
