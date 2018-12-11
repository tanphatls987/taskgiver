#include <ctime>
#include <string> 

using namespace std;

string getTodayName(){
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);
    int yy = currentTime->tm_year + 1900;
    int mm = currentTime->tm_mon + 1;
    int dd = currentTime->tm_mday;
    char s[7];
    sprintf(s, "%02d%02d%02d", yy%100, mm, dd);
    return string(s, 6);
}
string getTodayTime(){
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);
    int hh = currentTime->tm_hour;
    int mm = currentTime->tm_min;
    int ss = currentTime->tm_sec;
    char s[8];
    sprintf(s, "%02d:%02d:%02d", hh, mm, ss);
    return string(s, 8);
}
