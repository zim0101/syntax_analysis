#include "../include/validator.hpp"

int main() {
    string filePath = "input_file.txt";
    auto *validator = new Validator(filePath);
    validator->validateSyntax();

    return 0;
}