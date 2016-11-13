#include "myProcess.h"
#include <string>
#include <vector>

using namespace std;

myProcess::myProcess(string commandName, vector<string> listofArgs, int size) {

    command = commandName;
    myArgs = listofArgs;
    argCount = size;

}

string myProcess::getCommand() {
    return command;
}

vector<string> myProcess::getListOfArgs() {
    return myArgs;
}

int myProcess::getArgCount() {
    return argCount;
}
