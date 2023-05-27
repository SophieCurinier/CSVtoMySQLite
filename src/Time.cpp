#pragma once
#include <chrono>
#include <string>

using namespace std ;

class Time 
{
    public :
        static string getCurrentTime(){
            auto currentTime = chrono::system_clock::now();

            // Convertir l'heure actuelle en temps en utilisant le type time_t
            time_t time = chrono::system_clock::to_time_t(currentTime);

            // Convertir le temps en une représentation de chaîne de caractères
            stringstream ss;
            ss << put_time(localtime(&time), "%d/%m/%Y %H:%M:%S");

            return ss.str();
        }
};
