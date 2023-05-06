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

class AlarmEvent : public Event {
    public:
        string beginingTime ;
        string endingTime ;
        string description ;
        string recipent ;
        Action action ;

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
        }

    public:
        AlarmEvent(string begDateString, string begTimeString, string endDateString, string endTimeString, string descri, string recip, string act){
            beginingTime = parseStringToTime(begTimeString, begDateString);
            endingTime = parseStringToTime(endTimeString, endDateString);
            description = descri ;
            recipent = recip ;
            action.setAction(act) ;
        };

        AlarmEvent();

        string toSql() const override{
            stringstream ss;
            string act = action.getAction();
            ss << "INSERT INTO alarm (beginingTime, endingTime, description, recipent) VALUES (" << beginingTime << ", " << endingTime << ", '" << description << "', '"  << recipent << "');";;
            return ss.str();
        }

        void printEvent() const override {
            std::cout << beginingTime << " " << endingTime << " " << description << " " << recipent << " " << std::endl;
        };
};
