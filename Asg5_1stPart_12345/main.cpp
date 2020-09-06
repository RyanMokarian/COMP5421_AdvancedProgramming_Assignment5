/*
 * COMP 5421 Advanced Programming - Assignment 5 - part 1 (Task 1, 2, 3, 4 and 5)
 * Ryan Mokarian
 * Student Id: 40080413
 * Running Instruction: All tasks are run in the main (Dog.h and Dog.cpp are the required files).
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "Dog.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>     // std::istream_iterator
using std::vector;
using std::istream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std;

// Task (1) used function
void load_csvFile_Normal_Loop_task1(DogMapDefault& dog_map, std::string filename) {

    std::ifstream input_file_stream(filename); // Create an input file stream
    if (!input_file_stream.is_open()) {        // Check that the file is open
        cout << "Could not open file " + filename << endl;
        throw std::runtime_error("Could not open file " + filename);
    }
    std::string line;
    while (std::getline(input_file_stream, line)) {        // read a line
        std::stringstream my_line_stream(line); // turn the line into an input stream
        Dog dog{};
        my_line_stream >> dog;                  // initialize dog using Dog's operator>>
        dog_map.emplace(dog.getBreed(), dog);   // insert dog into dog_map
    //    dog_map.insert( std::pair<string ,Dog>(dog.getBreed(), dog) ); // alternative to emplace
    }
    input_file_stream.close(); // Close file
}

// Task (2) used function
void load_csvFile_For_Each(DogMapDefault& dog_map, std::string filename) {

    std::ifstream input_file_stream(filename); // Create an input file stream
    if (!input_file_stream.is_open()) {        // Check that the file is open
        cout << "Could not open file " + filename << endl;
        throw std::runtime_error("Could not open file " + filename);
    }

    // Get start of input stream and end of input stream iterators
    std::istream_iterator<Dog> input_stream_begin{ input_file_stream };
    std::istream_iterator<Dog> input_stream_end{};

    //     Copy Dog elements from input to dog_map using the for_each function
    std::string line;
    for_each(input_stream_begin, input_stream_end, [&dog_map](const Dog &dog){
        dog_map.emplace(dog.getBreed(), dog);
    });

    input_file_stream.close(); // Close file
}

// Task (3) used function
void load_csvFile_Transform(DogMapDefault& dog_map, std::string filename) {

    std::ifstream input_file_stream(filename); // Create an input file stream
    if (!input_file_stream.is_open()) {        // Check that the file is open
        cout << "Could not open file " + filename << endl;
        throw std::runtime_error("Could not open file " + filename);
    }

    // Get start of input stream and end of input stream iterators
    std::istream_iterator<Dog> input_stream_begin{ input_file_stream };
    std::istream_iterator<Dog> input_stream_end{};
    transform(input_stream_begin, input_stream_end,std::inserter(dog_map, dog_map.begin()), [] (const Dog &dog)
    {
        return std::make_pair(dog.getBreed(), dog);
    });

    input_file_stream.close(); // Close file
}

// Task (4) used function
void load_csvFile_Normal_Loop_task4(DogMapGreater& dog_map, std::string filename) {

    std::ifstream input_file_stream(filename); // Create an input file stream
    if (!input_file_stream.is_open()) {        // Check that the file is open
        cout << "Could not open file " + filename << endl;
        throw std::runtime_error("Could not open file " + filename);
    }
    std::string line;
    while (std::getline(input_file_stream, line)) {        // read a line
        std::stringstream my_line_stream(line); // turn the line into an input stream
        Dog dog{};
        my_line_stream >> dog;                  // initialize dog using Dog's operator>>
        dog_map.emplace(dog.getBreed(), dog);   // insert dog into dog_map
    }
    input_file_stream.close(); // Close file
}


int main() {
    DogMapDefault dogMap;
// Task (1)
    load_csvFile_Normal_Loop_task1(dogMap, "dogDB.csv");
    cout << "Task (1) Output:\n" << dogMap << endl;

// Task (2)
    dogMap.clear();
    load_csvFile_For_Each(dogMap, "dogDB.csv");
    cout << "\nTask (2) Output:\n"<< dogMap << endl;

// Task (3)
    dogMap.clear();
    load_csvFile_Transform(dogMap, "dogDB.csv");
    cout << "\nTask (3) Output:\n"<< dogMap << endl;

// Task (4)
    DogMapGreater dogMap2;
    load_csvFile_Normal_Loop_task4(dogMap2, "dogDB.csv");
    cout << "\nTask (4) Output:\n"<< dogMap2 << endl;

// Task (5)
    DogMapDefault dog_map;
    load_csvFile_Normal_Loop_task1(dog_map, "dogDB2.csv");
    DogMapDefault breedRangeMap1 = findBreedRange(dog_map, std::string("Greyhound"));
    cout << "\nTask (5) Output:\n"<< breedRangeMap1 << "----------" << endl;
    DogMapDefault breedRangeMap2 = findBreedRange(dog_map, std::string("Lakeland Terrier"));
    cout << breedRangeMap2 << "----------" << endl;
    DogMapDefault breedRangeMap3 = findBreedRange(dog_map, std::string("Pug"));
    cout << breedRangeMap3 << "----------" << endl;
    DogMapDefault breedRangeMap4 = findBreedRange(dog_map, std::string("Xyz"));
    cout << breedRangeMap4 << "----------" << endl;

    return 0;
}
