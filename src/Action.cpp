#include <string>
#include <stdexcept>

using namespace std;

class Action {
    string action ;

    public :
        void setAction(string act){
            if (act.compare("Ack") || act.compare("NotAck")){
                action = act;
            } else {
                throw invalid_argument("Action is invalid.");
            }
        }

        string getAction(){
            return action ;
        }
};
