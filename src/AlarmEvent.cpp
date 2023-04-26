#include <ctime>
#include <string>
#include "Action.cpp"

using std::string ;

class AlarmEvent {
    time_t beginingTime ;
    time_t endingTime ;
    string description ;
    string recipent ;
    Action action ;

    public:
        AlarmEvent(time_t begining, time_t ending, string descri, string recip, string act){
            beginingTime = begining ;
            endingTime = ending ;
            description = descri ;
            recipent = recip ;
            action.setAction(act) ;
        }
};
