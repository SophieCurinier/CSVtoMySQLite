#pragma once
#include "Action.cpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Event.cpp"

using std::string ;

class ChronoEvent : public Event {
    time_t dateTime;
    string recipent ;
    string action ;

    protected:
        void parseStringToTime(string time, string date, time_t* dateAndTime)  {
            try {
                // Convertir la date et l'heure en un objet tm
                std::tm tm = {};
                std::istringstream date_stream(date + " " + time);
                date_stream >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");

                // Convertir le tm en time_t
                *dateAndTime = std::mktime(&tm);
            } catch (std::exception& e) {
                // Gérer les erreurs de conversion
                std::cerr << "Erreur de conversion : " << e.what() << std::endl;
            }
        };

    public:
        ChronoEvent(string timeString, string dateString, string recip, string act){
            parseStringToTime(timeString, dateString, &dateTime);
            recipent = recip ;
            action = act ;
        };

        ChronoEvent();

        string insertToSql() const override{
            stringstream ss;
            ss << "INSERT INTO table_name (dateTime, action, recipent) VALUES (" << dateTime << ", " << action << "', '" << recipent << ")";
            return ss.str();
        }

        string selectToSql() const override{
            stringstream ss;
            ss << "SELECT * FROM chrono date = '" << dateTime << "', " << action << "', '" << recipent << ")";
            return ss.str();
        }


        void printEvent() const override {};
};
