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
        virtual std::string insertToSql() const = 0;

        virtual std::string selectToSql() const = 0;

        virtual void printEvent() const = 0;
};
