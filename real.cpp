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
        numPipes = 0;
        cout << "repl$ ";
        getline(cin, input);

        if (input.compare("quit") == 0 || (input.compare("logout")) == 0)
            return EXIT_SUCCESS;

        //declaration of variables used in char-iterating loop to build each myProcess object
        string commandName = "";
        const char * inputChars = input.c_str();
        bool sameCommand = true;

        for (int i = 0; i < input.length();) {
            int quotesCount = 0;
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
                        sizeWord = input.find(" ", i);
                        if (sizeWord == string::npos)
                            sizeWord = input.length();
                        string argName = (input.substr(i, (sizeWord - i)));
                        listArguments.push_back(argName);
                        int tempI = i;
                        i += (sizeWord - tempI);
                    }
                    else if (inputChars[i] == '"') { //needs to be changed to account for uneven quote number error
                        //quotesCount++;             //and quotes within quotes
                        //another count for \" and they need to both be even at end
                        cout << "inside quote if, i = " << i << endl;
                        int temp = i;
                        string tempName = "";
                        i++;
                        while (inputChars[i] != '"' && inputChars[i] != NULL) {
                            tempName += inputChars[i];
                            cout << tempName << endl;
                            i++;
                        }
                        tempName += inputChars[i];
                        listArguments.push_back(tempName.c_str());
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
