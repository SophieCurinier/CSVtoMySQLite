#pragma once
#include "Action.cpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using std::string ;

class Event {
    protected:
        void parseStringToTime();
    public:
        virtual std::string toSql() const = 0;

        virtual void printEvent() const = 0;
};
