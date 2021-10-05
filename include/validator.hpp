#ifndef SYNTAXANALYSIS_VALIDATOR_HPP
#define SYNTAXANALYSIS_VALIDATOR_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

class Validator {
public:
    string filePath;
    static const string alphaNumericRegex;
    static const string numericRegex;

    explicit Validator(string filePath);
    void validateSyntax();

private:
    static unordered_map<string, vector<string>> instructionMap();
    vector<string> getKeywordsFromLine(string line);
    bool lineMatchedWithInstructions(vector<string> instructionValues, vector<string> keys);

    vector<string> readFile();
};

#endif //SYNTAXANALYSIS_VALIDATOR_HPP