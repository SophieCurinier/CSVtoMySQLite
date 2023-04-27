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
        time_t beginingTime ;
        time_t endingTime ;
        string description ;
        string recipent ;
        Action action ;

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
        AlarmEvent(string begTimeString, string begDateString, string endTimeString, string endDateString, string descri, string recip, string act){
            parseStringToTime(begTimeString, begDateString, &beginingTime);
            parseStringToTime(endTimeString, endDateString, &endingTime);
            description = descri ;
            recipent = recip ;
            action.setAction(act) ;
        };

        AlarmEvent();
};
