#include <stdexcept>
#include <iostream>
#include <sqlite3.h>
#include "AlarmEvent.cpp"
#include "ChronoEvent.cpp"
#include <unistd.h>

using namespace std;

class SQLSender
{
    private:
        sqlite3* dataBase ;
        int openingDataBase ;
        string filename;

        void openingLinkDataBase(sqlite3* dataBase){
            if (access(filename.c_str(), F_OK) != 0) {
                std::cerr << "Le fichier de base de données n'existe pas." << std::endl;
                exit(EXIT_FAILURE);
            }
            openingDataBase = sqlite3_open(filename.c_str(), &dataBase);
            if (openingDataBase != SQLITE_OK){
                std::cerr << "Erreur lors de l'ouverture de la base de donnée : " << sqlite3_errmsg(dataBase) << std::endl;
                closingLinkDataBase(dataBase);
            } else {
                std::cout << "Database opening " << dataBase << std::endl;
            }
        }

        void closingLinkDataBase(sqlite3* dataBase){
            sqlite3_close(dataBase);
        }

        static int callback(void *isAlreadyInDataBasePtr, int argc, char **argv, char **azColName) {
            bool *isAlreadyInDataBase = static_cast<bool*>(isAlreadyInDataBasePtr);
            *isAlreadyInDataBase = true;
            return 0;
        }

        void insertRequest(sqlite3* dataBase, string table, Event* event){
            openingDataBase = sqlite3_open(filename.c_str(), &dataBase);
            if (openingDataBase != SQLITE_OK){
                std::cerr << "Erreur lors de l'ouverture de la base de donnée : " << sqlite3_errmsg(dataBase) << std::endl;
                closingLinkDataBase(dataBase);
            }
            sqlite3_stmt* stmt ;
            char *zErrMsg = 0;
            // Verify is already in database
            bool isAlreadyInDataBase = false;
            int preparingStatement ;
            const char* data = "Callback function called";
            string sqlStr = event->selectToSql();
            const char* sql = sqlStr.c_str();
            preparingStatement = sqlite3_exec(dataBase, sql, callback, &isAlreadyInDataBase, &zErrMsg);
            if (preparingStatement != SQLITE_OK){
                std::cerr << "Erreur lors de la selection de la requête : " << sqlite3_errmsg(dataBase) << std::endl;
                closingLinkDataBase(dataBase);
                exit (EXIT_FAILURE);
            }

            if (!isAlreadyInDataBase){
                sqlStr = event->insertToSql();
                sql = sqlStr.c_str();
                
                preparingStatement = sqlite3_exec(dataBase, sql, callback, 0, &zErrMsg);

                if (preparingStatement != SQLITE_OK){
                    std::cerr << "Erreur lors de la préparation de la requête : " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                    closingLinkDataBase(dataBase);
                    exit (EXIT_FAILURE);
                }
            }

            closingLinkDataBase(dataBase);

        }

        void setDBFilename(string fileName){
            filename = fileName ;
        }

    public:
        string getFilename(){
            return filename;
        }
        void fillDataBase(string fileName, vector<Event*>* events){
            setDBFilename(fileName);
            openingLinkDataBase(dataBase);

            for (const auto event : *events){
                if (auto alarmEvent = dynamic_cast<AlarmEvent*>(event)) {
                    insertRequest(dataBase, "alarm", alarmEvent);
                } else if (auto chronoEvent = dynamic_cast<ChronoEvent*>(event)) {
                    insertRequest(dataBase, "chrono", chronoEvent);
                } else {
                    std::cerr << "Erreur : événement non reconnu !" << std::endl;
                }
            }

            closingLinkDataBase(dataBase);
        }
};