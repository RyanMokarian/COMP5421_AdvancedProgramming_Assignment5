//
// Created by ryan on 2020-08-19.
//

#ifndef ASG5_1STPART_12345_DOG_H
#define ASG5_1STPART_12345_DOG_H

#include <map>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
using std::vector;
using std::istream;
using std::ostream;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std;

class Dog {
    std::string name;  std::string breed;  std::string age;  std::string gender;
public:
    Dog() = default; Dog(const Dog& ) = default; Dog& operator=(const Dog& ) = default;
    ~Dog() = default; Dog(      Dog&&) = default; Dog& operator=(      Dog&&) = default;

    Dog(std::string n, std::string b, std::string a, std::string g) :
            name(n), breed(b), age(a), gender(g) { }
    friend std::ostream &operator<<(std::ostream &, const Dog&);
    friend std::istream &operator>>(std::istream &, Dog &);
    // getter and setter member functions ..., such as
    std::string getBreed() const {return breed;}
};
using DogMapDefault = std::multimap<std::string, Dog>;
std::ostream &operator<<(std::ostream &, const DogMapDefault&);

using DogMapGreater = std::multimap<std::string, Dog, std::greater<std::string>>;
std::ostream &operator<<(std::ostream &, const DogMapGreater&);

string trim(const string & str);

DogMapDefault findBreedRange(DogMapDefault &source, const std::string &key_breed);

#endif //ASG5_1STPART_12345_DOG_H
