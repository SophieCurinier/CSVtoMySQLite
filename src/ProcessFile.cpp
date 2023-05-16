#include <dirent.h>
#include <iostream>
#include <functional>

class ProcessFile {
    public: 
        void processFiles(const std::string& dirname, const std::function<void(const std::string&)>& func) {
            DIR* dir = opendir(dirname.c_str());

            if (!dir) {
                std::cerr << "Erreur lors de l'ouverture du répertoire : " << dirname << std::endl;
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
                        std::cout << filename << std::endl;
                        func(filename) ;
                    }
                }
            }

            closedir(dir);
        }
};
