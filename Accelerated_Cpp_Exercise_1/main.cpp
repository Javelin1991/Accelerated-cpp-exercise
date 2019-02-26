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

void runProgrammeTwo();

int main()
{
    int programe_no = 2;
    if (programe_no == 2) {
        runProgrammeTwo();
        return 0;
    }
    
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
    
    return 0;
}

void runProgrammeTwo() {
    cout << "Please enter a string to be split: ";
    string s;
    while (getline(cin, s)) {
        vector<string> v = split(s);
        
        for(vector<string>::size_type i=0; i != v.size(); i++) {
            cout << v[i] << endl;
        }
    }
}

