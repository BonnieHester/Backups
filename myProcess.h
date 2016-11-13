#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <string>
#include <vector>

using namespace std;

class myProcess {

public:
    myProcess(string commandName, vector<string> listofArgs, int size);
    vector<string> getListOfArgs();
    int getArgCount();
    string getCommand();

private:
    string command;
    vector<string> myArgs;
    int argCount;
};

#endif //MYPROCESS_H
