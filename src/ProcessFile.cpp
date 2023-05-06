#include <dirent.h>
#include <iostream>

class ProcessFile {
    public: 
        void processFiles(const std::string& dirname) {
        DIR* dir = opendir(dirname.c_str());

        if (!dir) {
            std::cerr << "Erreur lors de l'ouverture du répertoire : " << dirname << std::endl;
            return;
        }

        struct dirent* entry;

        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_DIR && std::string(entry->d_name) != "." && std::string(entry->d_name) != "..") {
                std::string subdir = dirname + "/" + entry->d_name;
                processFiles(subdir); // Récursion pour explorer les sous-répertoires
            }
            else if (entry->d_type == DT_REG) {
                std::string filename = dirname + "/" + entry->d_name;
                std::cout << "Hello " + filename << std::endl;
            }
        }

        closedir(dir);
        }
};
