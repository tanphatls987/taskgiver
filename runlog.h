#include <string>
#include <fstream> 
#include "time_mag.h"
using namespace std;

class logRecorder{
private:
    string dir;
public:
    logRecorder(const string& fileName){
        dir = "runlog/" + fileName + ".log";
    }

    void record(const string& action,const string& name){        
        ofstream logOut;
        logOut.open(dir, ios::out | ios::app);
        logOut << getTodayTime() + "|[" + action + "]" + name + '\n';
        logOut.close();
    }
};
