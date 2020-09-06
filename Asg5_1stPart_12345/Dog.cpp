//
// Created by ryan on 2020-08-19.
//

#include "Dog.h"
#include<iomanip>
#include <regex>

std::ostream &operator<<(std::ostream &sout, const Dog &dog) {
    sout << dog.name << ", " << dog.breed << ", " << dog.age << ", " << dog.gender;
    return sout;
}

std::istream &operator>>(std::istream &sin, Dog &dog) {
// trim() removes leading and trailing whitespace of its argument
    std::getline(sin, dog.name, ',');
    dog.name   = trim(dog.name);
    std::getline(sin, dog.breed, ',');
    dog.breed  = trim(dog.breed);
    std::getline(sin, dog.age, ',');
    dog.age    = trim(dog.age);
    std::getline(sin, dog.gender);
    dog.gender = trim(dog.gender);

// Input Validation
    std::regex stringpattern("[a-zA-Z\\-\\ \r]*");
    std::regex digitpattern("[0-9]*");
    if (std::regex_match(dog.name, stringpattern) == 0)
        throw std::runtime_error("The dog name input is invalid.");
    if (std::regex_match(dog.breed, stringpattern) == 0)
        throw std::runtime_error("The dog breed input is invalid.");
    if (std::regex_match(dog.age, digitpattern) == 0)
        throw std::runtime_error("The dog age input is invalid.");
    if (std::regex_match(dog.gender, stringpattern) == 0)
        throw std::runtime_error("The dog gender input is invalid.");

    return sin;
}

std::ostream &operator<<(std::ostream &sout, const DogMapDefault & dogmap) {
    for (const auto & [breed, dog] : dogmap) { // C++17
        std::cout << std::setw(25) << breed << " --> " << dog << std::endl;
    }
    return sout;
}

std::ostream &operator<<(std::ostream &sout, const DogMapGreater & dogmap) {
    for (const auto & [breed, dog] : dogmap) { // C++17
        std::cout << std::setw(25) << breed << " --> " << dog << std::endl;
    }
    return sout;
}

string trim(const string & str) {
    const std::string WHITESPACE = " ";
    string trimed_str(str);

    size_t start = str.find_first_not_of(WHITESPACE);
    if (start == std::string::npos) trimed_str="";
    else trimed_str=str.substr(start);

    size_t end = trimed_str.find_last_not_of(WHITESPACE);
    if (end == std::string::npos) trimed_str="";
    else trimed_str=trimed_str.substr(0, end + 1);

    return trimed_str;
}

DogMapDefault findBreedRange(DogMapDefault &source, const std::string &key_breed)
{
    DogMapDefault breedRangeMap;

    std::pair<std::multimap<std::string, Dog>, std::multimap<std::string, Dog>> bound;
    for (std::multimap<std::string, Dog>::iterator it=source.equal_range (key_breed).first; it!=source.equal_range (key_breed).second; ++it)
        breedRangeMap.emplace(key_breed, it->second);

    return breedRangeMap;
}
