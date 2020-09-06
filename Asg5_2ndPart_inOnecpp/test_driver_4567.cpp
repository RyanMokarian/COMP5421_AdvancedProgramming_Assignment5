/*
 * COMP 5421 Advanced Programming - Assignment 5 - part 2 (Problems 4, 5, 6 and 7)
 * Ryan Mokarian
 * Student Id: 40080413
 * Running Instruction: All tasks are run in the main of this file.
 */

#include <iostream>
using namespace std;
#include <algorithm>
#include <array>
#include <iterator>
#include <vector>
#include <string>
#include <map>
#include <set>


// PROBLEM 4: ****************************************************************************************

bool is_palindrome(const string& phrase) {

    string temp;
    string::iterator it = temp.begin();
    string::const_iterator begin = phrase.begin();
    string::const_iterator ends = phrase.end();

    remove_copy_if(begin, ends, inserter(temp, it), [](char x) {return !isalpha(x); });// lambda function return only alphabet
    transform(temp.begin(), temp.end(), temp.begin(), [](char x) {return tolower(x); });// lambda function return lower case

    return equal(temp.begin(),temp.end(),temp.rbegin());// compare from start to end with from end to start;
}

void test_is_palindrome()
{
    std::string str_i = std::string("was it a car or A Cat I saW?");
    std::string str_u = std::string("was it A Car or a cat U saW?");
    cout << "the phrase \"" + str_i + "\" is " +
            (is_palindrome(str_i) ? "" : "not ") + "a palindrome\n";
    cout << "the phrase \"" + str_u + "\" is " +
            (is_palindrome(str_u) ? "" : "not ") + "a palindrome\n";
}

// PROBLEM 5: ****************************************************************************************

    // function to find second largest value
template <class Iterator>
pair<Iterator, bool>
second_max(Iterator start, Iterator finish)
{
    // tests if set is empty
    if (start == finish)
        return make_pair(finish, false);
    else {
        Iterator current = start;
        Iterator largest = start;
        Iterator secondLargest = start;

        // iterates through set, keeping secondLargest behind largest
        while (current != finish) {
            if (*largest < *current) {
                secondLargest = largest;
                largest = current;
            }
            current++;
        }

        // if largest and secondLargest are same, all values must be equal
        if (*largest == *secondLargest) {
            return make_pair(start, false);
        }
            // returns secondLargest
        else
            return make_pair(secondLargest, true);
    }
}

    // test function to test & display secondLargest
void test_second_max(vector<int> vec)
{
    auto retval = second_max(vec.begin(), vec.end());

    if (retval.second)
    {
        cout << "The second largest element in vec is "
             << *retval.first << endl;
    }
    else
    {
        if (retval.first == vec.end())
            cout << "List empty, no elements\n";
        else
            cout << "Container's elements are all equal to "
                 << *retval.first << endl;
    }
}

// PROBLEM 6: ****************************************************************************************

    // lambda function to count number of n-length strings
auto countStringLambda = [](const vector<string> vec,int n) -> int {
    return count_if(vec.begin(), vec.end(), [n](auto stringElement) {return stringElement.length() == n; });
};

int testCountStringsLambda (const std::vector<std::string>& vec, int n){
    return countStringLambda(vec, n);
}

    // free function to count number of n-length strings
int countStringFreeFun(const vector<std::string> &vec, int n){
    int lambdaStringCount = count_if(vec.begin(), vec.end(), [n](auto stringElement)
    {return stringElement.length() == n; });
    return lambdaStringCount;
}

int testCountStringsFreeFun (const std::vector<std::string>& vec, int n){
    return countStringFreeFun(vec, n);
}

    // functor to count number of n-length strings
struct countStringFunctor {
    vector<string> stringVector;
    int n;
    // functor constructor
    countStringFunctor(vector<string> stringVector, int n) : stringVector(stringVector), n(n) {}
    // operator() overload
    int operator() (vector<string> vec, int n) { return count_if(vec.begin(), vec.end(),
                                               [n](auto stringElement) {return stringElement.length() == n; }); }
    // operator << overload for output
    friend ostream& operator<<(ostream& out, const countStringFunctor& givenCsf)
    { auto csf = givenCsf;  return out << csf.operator()(csf.stringVector, csf.n); }
};

int testCountStringsFunctor (const std::vector<std::string>& vec, int n){
    countStringFunctor obj(vec, n);
    return obj(vec, n);
}

// PROBLEM 7: ****************************************************************************************

    // orders strings by length as priority, then by alphabetical order
struct problem7_Sorting {
    bool operator()(const string& s1, const string& s2) const {
        if (s1.length() == s2.length()) {
            return (s1 < s2);
        }
        return (s1.length() < s2.length());
    }
};

    // creates reordered set of test strings
void multisetUsingMyComparator() {
    // creates multiset which calls problem7_Sorting on newly added strings
    multiset<string, problem7_Sorting> strSet;

    vector<string> vec{ "C", "BB", "A", "CC", "A", "B",
                        "BB", "A", "D", "CC", "DDD", "AAA" };

    // inserts test strings in multiset
    copy(vec.begin(), vec.end(), inserter(strSet, strSet.begin()));

    // outputs strings from the multiset
    ostream_iterator<string> out(cout, " ");
    copy(strSet.begin(), strSet.end(), out);
}

int main()
{
// Problem 4:
    test_is_palindrome();
    cout << "\n";

// Problem 5:
    std::vector<int> v1{ 1 }; // one element
    test_second_max(v1);

    std::vector<int> v2{ 1, 1 }; // all elements equal
    test_second_max(v2);

    std::vector<int> v3{ 1, 1, 3, 3, 7, 7 }; // at least with two distinct elements
    test_second_max(v3);
    cout << "\n";

// problem 6:
    std::vector<std::string> vecstr
            { "C", "BB", "A", "CC", "A", "B",
              "BB", "A", "D","CC", "DDD", "AAA"};
    cout << testCountStringsLambda(vecstr, 1) << endl;
    cout << testCountStringsFreeFun(vecstr, 1) << endl;
    cout << testCountStringsFunctor(vecstr, 1) << endl;
    cout << "\n";

// problem 7:
    multisetUsingMyComparator();
    cout << "\n";

    return 0;
}



