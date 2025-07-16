#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//get file from user
string getFileDirectory() {
    string directory;
    cout << "Enter the directory of the file you want to read here ";
    cin >> directory;

    return directory;
}

//read from file; store information in struct variables; return list of struct variables
vector<string> readFromFile(string fileName) {
    vector<string> listOfLines;
    auto fileOpened = false;
    while (!fileOpened) {
        ifstream file(fileName);
        if (file.is_open()) {
            //read by line
            string fileLine;
            while (getline(file, fileLine)) {
                listOfLines.push_back(fileLine);
            }
            fileOpened = true;
        }
        else {
            cout << "File not found\n";
            getFileDirectory();
        }
    }
    
    return listOfLines;
}

map<string, string> listToMap(string fileName) {
    //store all info on each tag together
    map<string, string>tags = {};
    int counter = 0;

    vector<string> list = readFromFile(fileName);
    for (int i = 0;i < list.size();i++) {
        // make unique key with name so that map will be automatically sorted
        string uniqueKey;
        auto nameFound = false;
        int nameCounter = 0;
        while (!nameFound) {
            if (list[i][nameCounter] == ',') {
                nameFound = true;
            }
            else {
                uniqueKey += list[i][nameCounter];
                nameCounter++;
            }
        }
        uniqueKey += to_string(counter);

        //add list line to map with key of [line name][incrementing counter]
        tags[uniqueKey] = list[i];
        counter++;
    }
    
    return tags;
}

//output in alpha order and number of lines
int outputMap(string fileName) {
    map<string, string> MAP = listToMap(fileName);
    for (auto value : MAP) {
        cout << value.second << "\n\n";
    }
    return 0;
}

int main(int argc, char* argv[])
{
    string FILE;
    if (argc > 1) {
        FILE = argv[1];
    }
    else {
        FILE = getFileDirectory();
    }
    outputMap(FILE);
}