#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include "grade.hpp"
#include "Student_Info.hpp"
#include "extract_fails.hpp"
#include "helper.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::domain_error;
using std::max;
using std::setprecision;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;
using std::list;

void runGradeCalculator();
void runStringSplitter();
void runStringFrameConcatenator();
void test();

int main()
{
    int programmeChoice;
    cout << "Choose which programme to run: " << endl;
    cout << "(1) Grade Calculator" << endl;
    cout << "(2) String Splitter" << endl;
    cout << "(3) String Frame Concatenator" << endl;
    cout << "(4) Rotate" << endl;

    cin >> programmeChoice;
    
    switch (programmeChoice) {
        case 1:
            runGradeCalculator();
            break;
        case 2:
            runStringSplitter();
            break;
        case 3: runStringFrameConcatenator();
            break;
        case 4: test();
            break;
    }
    return 0;
}

void runGradeCalculator() {
    list<Student_info> students;
    vector<double> homework;
    Student_info record;
    int maxlen = 0;   // the length of the longest name
    
    // read and store all the student's data.
    // Invariant:   students contain all the student records read so far
    //              maxlen contains the length of the longest name in students
    
    while (true)
    {
        // find the length of longest name
        string name;
        double midterm_score;
        double final_score;
        cout << "Please enter student name: ";
        cin >> name;
        if (name[0] == '#') {
            break;
        }
        cin.get();
        cout << "Please enter midterm score: ";
        cin >> midterm_score;
        cout << "Please enter final score: ";
        cin >> final_score;
        cout << "Please enter homework score: ";
        read_hw(cin, homework);
        record = {name, midterm_score, final_score, homework};
        maxlen = std::max(maxlen, (int) record.name.size());
        students.push_back(record);
        cin.clear();
    }
    
    
    // write the names and grades
    // Extract the failed students
    list<Student_info> students_failed = extract_fails(students);
    
    // sort lists
    students_failed.sort(compare);
    
    // Report passing students
    cout << "These students have passed." << endl;
    print(students, maxlen);
    // Report failing students
    cout << "These students have failed." << endl;
    print(students_failed, maxlen);
}

void runStringSplitter() {
    cout << "Please enter a string to be split: ";
    string s;
    while (getline(cin, s)) {
        vector<string> v = split(s);
        
        for(vector<string>::size_type i=0; i != v.size(); i++) {
            cout << v[i] << endl;
        }
    }
}

void runStringFrameConcatenator() {
    string input;
    vector<string> vet;
    getchar();
    while (true) {
        cout << "Please enter a string: ";
        getline(cin, input);

        if (input[0] == '#') {
            break;
        }
        vet.push_back(input);
        cin.clear();
    }
    frame(vet);
    printVector(vet);
}

void test() {
    string input;
    vector<string> vet;
    getchar();
    while (true) {
        cout << "Please enter a string: ";
        getline(cin, input);
        
        if (input[0] == '#') {
            break;
        }
        vet.push_back(input);
        cin.clear();
    }
    vector<string> final_result = rotate(vet);
    
    for(string::size_type i=0; i != final_result.size(); i++) {
        cout << final_result[i] << endl;
    }
}
