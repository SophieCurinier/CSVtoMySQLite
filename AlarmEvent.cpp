#include <ctime>
#include <string>

using std::string ;

class AlarmEvent {
    time_t beginingTime ;
    time_t endingTime ;
    string description ;
    string recipent ;
    string action ;
};
