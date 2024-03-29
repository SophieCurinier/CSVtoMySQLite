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

using namespace std;

class AlarmEvent : public Event {
    public:
        string beginingTime ;
        string endingTime ;
        string description ;
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
            } catch (exception& e) {
                // Gérer les erreurs de conversion
                LogFile::instance()->logError(Time::getCurrentTime() + " - Conversion error : " + e.what());
                return "";
            }
        }

    public:
        AlarmEvent(string begDateString, string begTimeString, string endDateString, string endTimeString, string descri, string recip, string act){
            beginingTime = parseStringToTime(begTimeString, begDateString);
            endingTime = parseStringToTime(endTimeString, endDateString);
            description = removeSpecialCharacters(descri);
            recipent = removeSpecialCharacters(recip);
            action = removeSpecialCharacters(act);
        };

        AlarmEvent();

        string insertToSql() const override{
            stringstream ss;
            ss << "INSERT INTO alarm (date_debut, date_fin, description, destinataire) VALUES ('" << beginingTime << "', '" << endingTime << "', '" << description << "', '"  << recipent << "');";;
            return ss.str();
        }

        string selectToSql() const override{
            stringstream ss;
            ss << "SELECT * FROM alarm WHERE date_debut = '" << beginingTime << "' AND date_fin = '" << endingTime << "' AND description = '" << description << "' AND destinataire = '"  << recipent << "';";;
            return ss.str();
        }

        void printEvent() const override {};
};
