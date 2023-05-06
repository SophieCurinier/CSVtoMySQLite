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
            }
        }

        void closingLinkDataBase(sqlite3* dataBase){
            sqlite3_close(dataBase);
        }

        void insertRequest(sqlite3* dataBase, string table, Event* event){
            sqlite3_stmt* stmt ;
            
            int preparingStatement ;
            int insertingStatement ;
            string sqlStr = event->toSql();
            // const char* sql = sqlStr.c_str();
            // std::cout << sql << std::endl;
            const char *sql = "CREATE TABLE 'bidule' (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
            preparingStatement = sqlite3_prepare_v2(dataBase, sql, -1, &stmt, NULL) ;

            if (preparingStatement != SQLITE_OK){
                std::cerr << "Erreur lors de la préparation de la requête : " << sqlite3_errmsg(dataBase) << std::endl;
                closingLinkDataBase(dataBase);
                exit (EXIT_FAILURE);
            } 

            insertingStatement = sqlite3_step(stmt) ;

            if (insertingStatement != SQLITE_DONE) {
                std::cerr << "Error inserting data: " << sqlite3_errmsg(dataBase) << std::endl ;
                closingLinkDataBase(dataBase) ;
                exit (EXIT_FAILURE);
            }

            sqlite3_finalize(stmt) ;
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
            // for (const auto event : events){
            //     std::cout << "Test " << std::endl;
            //     if (typeid(event) == typeid(AlarmEvent)) {
            //         std::cout << "Test 2" << std::endl;
            //         //insertRequest(dataBase, "alarm", *alarmEvent);
            //     } else if (typeid(event) == typeid(ChronoEvent)) {
            //         //insertRequest(dataBase, "chrono", *chronoEvent);
            //     } else {
            //         std::cerr << "Erreur : événement non reconnu !" << std::endl;
            //     }
            // }
            closingLinkDataBase(dataBase);
        }
};