#include <bits/stdc++.h>
#include <ctime>
#include "trie.h"
#include "runlog.h"
#include "time_mag.h"


using namespace std;

trie genericTree;
string todayName;

bool askQuestion(const string& question) {
    cout << question << " ";
    char answer;
    cin >> answer;

    bool result = answer == 'y';
    return result;
}
bool loadQuestion(){
    ///simple ask screen
    system("clear");
    cout<< "Day:" << todayName << '\n';
    ///will be upgraded to script 
    if (askQuestion("Need a job?")) return 1;
    else {
        cout<<"Mistake were made\n";
        return 0;
    }
}


void buildGenericTaskTree(){
    ///can modified generic text manually
    ifstream genInp("generic.txt");
    string s;
    while (getline(genInp, s)){
        genericTree.insert(s);
    }
    genInp.close();
}
void fillTodayJob(const string& logFileName,trie* genericTree){
    ///don't recognize old job
    ifstream todayInp("log/"+logFileName+".txt");
    cout << "Done list:" <<'\n';
    if (!todayInp.fail()){
        string s;
        while (getline(todayInp, s)) {
            cout << "-" << s <<'\n';
            genericTree->markFinish(s);
        }
    }
    todayInp.close();
}
void clearTaskLog(const string& logFileName){
    system(("rm log/" + logFileName).c_str());
}
vector <trieNode*> loadRemainTaskToday(){
    string logFileName = getTodayName();
    buildGenericTaskTree();
    fillTodayJob(logFileName, &genericTree);
    return genericTree.getFreeEnd(1);
}


int getRandomTask(int n) {
    srand(time(NULL));
    int select = rand() % n;
    return select;
}

void exportDoneTask(vector<trieNode*> &taskList, const int &showTask) {
    ofstream todayOut("log/" + todayName +".txt",
        ios::out | ios::app);
    todayOut << genericTree.retrieveName(taskList[showTask]) << '\n';

    todayOut.close();
    taskList[showTask] = taskList.back();
    taskList.pop_back();
    ///something for log file

}
bool doRandomTask(vector<trieNode*> &taskList, logRecorder* logRec) {
    if (taskList.empty()) {
        cout << "All done today\n";
        return false;
    }
    int showTask = getRandomTask(taskList.size());
    string taskName = genericTree.retrieveName(taskList[showTask]);
    cout << "Current task: " << genericTree.retrieveName(taskList[showTask]) << '\n';
    logRec->record("GIVE", taskName);        
    if (askQuestion("Did you finish it?:")) { 
        exportDoneTask(taskList, showTask);
        logRec->record("DONE", taskName);
    }
    ///
    return false;
}
void showRemainTask(const vector<trieNode*> &taskList){
    cout << "Remaining task:\n";
    for(auto i : taskList) 
        cout << " -" << genericTree.retrieveName(i) <<'\n';
}

void run() {
    todayName = getTodayName();
    if (!loadQuestion()) return;
    ///
    logRecorder* logRec = new logRecorder(todayName);
    vector<trieNode*> taskList = loadRemainTaskToday();
    showRemainTask(taskList);
    while (true){
        doRandomTask(taskList, logRec);
        if (!askQuestion("More job?")) break;
    }
}
int main() {
    run();
}
