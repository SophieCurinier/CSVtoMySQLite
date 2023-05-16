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

using namespace std ;

class ChronoEvent : public Event {
    string dateTime;
    string recipent ;
    string action ;

    protected:
        string parseStringToTime(string time, string date) {
            try {
                // Convertir la date et l'heure en un objet tm
                std::tm tm = {};
                std::istringstream date_stream(date + " " + time);
                date_stream >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");

                // Convertir le tm en time_t
                std::stringstream ss;
                ss << std::put_time(&tm, "%d/%m/%Y %H:%M:%S");
                return ss.str();
            } catch (std::exception& e) {
                // Gérer les erreurs de conversion
                std::cerr << "Erreur de conversion : " << e.what() << std::endl;
                return "";
            }
        };

    public:
        ChronoEvent(string dateString, string timeString, string recip, string act){
            dateTime = parseStringToTime(timeString, dateString);
            recipent = removeSpecialCharacters(recip);
            action = removeSpecialCharacters(act);
        };

        ChronoEvent();

        string insertToSql() const override{
            stringstream ss;
            ss << "INSERT INTO chrono (date, destinataire, action) VALUES ('" << dateTime << "', '" << recipent << "', '" << action << "')";
            return ss.str();
        }

        string selectToSql() const override{
            stringstream ss;
            ss << "SELECT * FROM chrono WHERE date = '" << dateTime << "' AND action = '" << action << "' AND destinataire = '" << recipent << "'";
            return ss.str();
        }


        void printEvent() const override {};
};
