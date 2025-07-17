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

map<string, int> listToMap(string fileName) {
    //store all info on each tag together
    map<string, int>tags = {};
    int counter = 0;

    vector<string> list = readFromFile(fileName);
    for (int i = 0;i < list.size();i++) {
        //check if tag name is in map
        for (const auto value : tags) {
            auto found = false;
            if (value.first == list[i]) {
                tags[value.first] += 1;
            }
            // if tag name is not in map adds it to map
            if (!found) {
                tags[list[i]] = 1;
            }
        }
    }
    
    return tags;
}

//output in alpha order and number of lines
int outputMap(string fileName) {
    map<string, int> MAP = listToMap(fileName);
    for (auto value : MAP) {
        cout << value.first << ": " << value.second << " lines \n\n";
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
