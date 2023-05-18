#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Event.cpp"
#include "LogFile.cpp"
#include "Time.cpp"



using namespace std ;

class ChronoEvent : public Event {
    string dateTime;
    string recipent ;
    string action ;

    protected:
        string parseStringToTime(string time, string date) {
            try {
                // Convertir la date et l'heure en un objet tm
                tm tm = {};
                istringstream date_stream(date + " " + time);
                date_stream >> get_time(&tm, "%d/%m/%Y %H:%M:%S");

                // Convertir le tm en time_t
                stringstream ss;
                ss << put_time(&tm, "%d/%m/%Y %H:%M:%S");
                return ss.str();
            } catch (exception& e){
                // Gérer les erreurs de conversion
                LogFile::instance()->logError(Time::getCurrentTime() + " - Conversion error : " + e.what());
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
