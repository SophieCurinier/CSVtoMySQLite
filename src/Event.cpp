#pragma once
#include "Action.cpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Event {
    protected:
        void parseStringToTime();
        std::string removeSpecialCharacters(std::string str){
            std::string result ;
            for (char c : str){
                if (std::isalnum(c) || c == '-' || c == '_' || c == '*' || c == '.' || c == '(' || c == ')' || c == ' '){
                    result += c;
                }
            }
            return result;
        }
    public:
        virtual std::string insertToSql() const = 0;

        virtual std::string selectToSql() const = 0;

        virtual void printEvent() const = 0;
};
