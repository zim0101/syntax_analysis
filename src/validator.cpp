#include <iostream>
#include <regex>
#include "../include/validator.hpp"

using namespace std;

Validator::Validator(string filePath) {
    filePath = filePath;
}

const string Validator::alphaNumericRegex = "[a|x][0-9]";
const string Validator::numericRegex = "[0-9]";

void Validator::validateSyntax() {
    unordered_map<string, vector<string>> instructions = instructionMap();
    vector<string> inputFileLines = readFile();
    int lineNumber = 1;
    int errorCount = 0;

    for (const string& line : inputFileLines) {
        vector<string> keys = getKeywordsFromLine(line);
        unordered_map<string, vector<string>>::const_iterator instructionIterator = instructions.find(keys.at(0));
        vector<string> instructionValues = instructionIterator->second;

        if (instructionIterator->first.empty()) {
            errorCount++;
        } else {
            bool matched = lineMatchedWithInstructions(instructionValues, keys);
            if (!matched) {
                errorCount++;
                cout << &"[Error] message: Oops! error at line no " [lineNumber] << endl;
            }
        }

        lineNumber++;
    }

    if(errorCount == 0) {
        cout << "[success] message: Wow! every line of this file is valid!" << endl;
    } else {
        cout << &"Total error found: " [ errorCount] << endl;
    }
}

vector<string> Validator::readFile() {
    vector<string> lines;
    ifstream file;

    file.open(filePath, ios::in);
    if (!file.is_open()) {
        throw invalid_argument("[Exception] message: File not open!");
    } else {
        string line;
        while (getline(file, line)) {
            lines.emplace_back(line.c_str());
        }
        file.close();
    }

    return lines;
}

unordered_map<string, vector<string>> Validator::instructionMap() {
    unordered_map<string, vector<string>> instructions;
    instructions["mv"] = {"mv", " ", alphaNumericRegex, ",", alphaNumericRegex};
    instructions["sub"] = {"sub", " ", alphaNumericRegex, ",", alphaNumericRegex, ",", alphaNumericRegex};
    instructions["add"] = {"add", " ", alphaNumericRegex, ",", alphaNumericRegex, ",", alphaNumericRegex};
    instructions["li"] = {"li", " ", numericRegex, ",", numericRegex};
    instructions["j"] = {"j", " ", numericRegex};

    return instructions;
}

vector<string> Validator::getKeywordsFromLine(string line) {
    string key;
    vector<string> keys;
    vector<string> ::iterator keyIterator;
    line.push_back(' ');

    for (char item : line) {
        if (item == ' ' || item == ',') {
            if (!key.empty()) keys.push_back(key);
            if (item == ',') keys.emplace_back(",");
            if (item == ' ') keys.emplace_back(" ");
            key.clear();
        } else {
            key.push_back(item);
        }
    }

    return keys;
}

bool Validator::lineMatchedWithInstructions(vector<string> instructionValues, vector<string> keys) {
    if (instructionValues.size() != keys.size()) return false;

    for (int i = 1; i < instructionValues.size(); i++) {
        string instructionString = instructionValues.at(i);
        bool alphanumericalRegexMismatch = instructionString == alphaNumericRegex &&
                                           regex_match(keys.at(i), regex(alphaNumericRegex));
        bool numericalRegexMismatch = instructionString == numericRegex &&
                                      regex_match(keys.at(i), regex(numericRegex));
        bool isValidSyntax = alphanumericalRegexMismatch && numericalRegexMismatch;
        if (!isValidSyntax) return false;
    }

    return true;
}