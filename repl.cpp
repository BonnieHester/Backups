#include <iostream>
#include <string>
#include "myProcess.h"
#include <vector>

using namespace std;

int main() {

    int numPipes = 0;
    string input = "";
    string jobIn = "STDIN_FILENO";
    string jobOut = "STDOUT_FILENO";
    string jobErr = "STDERR_FILENO";

    vector<myProcess> allProcesses;
    vector<myProcess>::iterator allProcessesIter;

    vector<string> listArguments;
    vector<string>::iterator listArgsIter;

    while ((input.compare("quit")) != 0 && (input.compare("logout")) != 0) {

        allProcesses.clear();
        listArguments.clear();
        jobIn = "STDIN_FILENO";
        jobOut = "STDOUT_FILENO";
        jobErr = "STDERR_FILENO";
        numPipes = 0;
        cout << "\nrepl$ ";
        getline(cin, input);

        if (input.compare("quit") == 0 || (input.compare("logout")) == 0)
            return EXIT_SUCCESS;

        //declaration of variables used in char-iterating loop to build each myProcess object
        string commandName = "";
        const char * inputChars = input.c_str();
        bool sameCommand = true;

        for (int i = 0; i < input.length();) {
            sameCommand = true;
            if (inputChars[i] != '|' && inputChars[i] != '"') {
                while (inputChars[i] == ' ')
                    i++;
                size_t sizeWord = input.find(" ", i);
                if (sizeWord == string::npos)
                    sizeWord = input.length();
                commandName = input.substr(i, (sizeWord - i));
                int temp = i;
                i += (sizeWord - temp);
                while (sameCommand && inputChars[i] != NULL) {
                    while (inputChars[i] == ' ')
                        i++;
                    if (inputChars[i] != '|' && inputChars[i] != '"') {

                        if (input.find("< ", i) == i) {
                            i += 2;
                            sizeWord = input.find(" ", i);
                            if (sizeWord == string::npos)
                                sizeWord = input.length();
                            string arg = (input.substr(i, (sizeWord - i)));
                            jobIn = arg;
                            int tempI = i;
                            i += (sizeWord - tempI);
                        }
                        else if (input.find("e> ", i) == i) {
                            i += 3;
                            sizeWord = input.find(" ", i);
                            if (sizeWord == string::npos)
                                sizeWord = input.length();
                            string arg = (input.substr(i, (sizeWord - i)));
                            jobErr = arg;
                            jobErr += " (truncate)";
                            int tempI = i;
                            i += (sizeWord - tempI);
                        }
                        else if (input.find("e>> ", i) == i) {
                            i += 4;
                            sizeWord = input.find(" ", i);
                            if (sizeWord == string::npos)
                                sizeWord = input.length();
                            string arg = (input.substr(i, (sizeWord - i)));
                            jobErr = arg;
                            jobErr += " (append)";
                            int tempI = i;
                            i += (sizeWord - tempI);
                        }
                        else if (input.find("> ", i) == i) {
                            i += 2;
                            sizeWord = input.find(" ", i);
                            if (sizeWord == string::npos)
                                sizeWord = input.length();
                            string arg = (input.substr(i, (sizeWord - i)));
                            jobOut = arg;
                            jobOut += " (truncate)";
                            int tempI = i;
                            i += (sizeWord - tempI);
                        }
                        else if (input.find(">> ", i) == i) {
                            i += 3;
                            sizeWord = input.find(" ", i);
                            if (sizeWord == string::npos)
                                sizeWord = input.length();
                            string arg = (input.substr(i, (sizeWord - i)));
                            jobOut = arg;
                            jobOut += " (append)";
                            int tempI = i;
                            i += (sizeWord - tempI);
                        }
                        else {
                            sizeWord = input.find(" ", i);
                            if (sizeWord == string::npos)
                                sizeWord = input.length();
                            string argName = (input.substr(i, (sizeWord - i)));
                            listArguments.push_back(argName);
                            int tempI = i;
                            i += (sizeWord - tempI);
                        }
                    }
                    else if (inputChars[i] == '"') { //needs to be changed to account for uneven quote number error
                        bool inQuote = true;
                        string tempName = "";
                        i++;
                        while (inQuote &&inputChars[i] != NULL) {
                            if (inputChars[i] != '"') {
                                if (inputChars[i] != '\\')
                                    tempName += inputChars[i];
                            }
                            else {
                                if (inputChars[i-1] == '\\')
                                    tempName += inputChars[i];
                                else
                                    inQuote = false;
                            }
                            i++;
                        }
                        i++;
                        listArguments.push_back(tempName);
                    }
                    else if (inputChars[i] == '|') {
                        myProcess newProcess(commandName, listArguments, listArguments.size());
                        allProcesses.push_back(newProcess);
                        i++;
                        numPipes++;
                        sameCommand = false;
                        listArguments.clear();
                    }
                }
            }
            //deal with leading off with | or "
        }
        myProcess newProcess(commandName, listArguments, listArguments.size());
        allProcesses.push_back(newProcess);

        cout << "\nJob STDIN  = " << jobIn << endl;
        cout << "Job STDOUT = " << jobOut << endl;
        cout << "Job STDERR = " << jobErr << endl;

        cout << '\n' << numPipes << " pipe(s)" << endl;
        cout << allProcesses.size() << " process(es)" << endl;

        int counter = 0;

        //use iter to iterate through and print info about each process
        for (allProcessesIter = allProcesses.begin(); allProcessesIter != allProcesses.end(); allProcessesIter++) {
            cout << "\nProcess " << counter << " argv:" << endl;
            counter++;
            myProcess tempProcess = *allProcessesIter;

            vector<string> tempList = tempProcess.getListOfArgs();
            vector<string>::iterator tempListIter;
            string nameOfCommand = tempProcess.getCommand();

            cout << "0: " << nameOfCommand << endl;
            int listCounter = 1;

            for (tempListIter = tempList.begin(); tempListIter != tempList.end(); tempListIter++) {
                cout << listCounter << ": " << *tempListIter << endl;
                listCounter++;
            }

        }
        cout << endl;

    }

}
