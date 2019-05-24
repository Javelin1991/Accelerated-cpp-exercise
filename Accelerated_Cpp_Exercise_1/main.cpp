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
void permutatePageIndex();

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
        case 4: permutatePageIndex();
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
//    students_failed.sort(compare);
    
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
    vector<string> outcome = frame(vet, false);
    printVector(outcome);
}

void permutatePageIndex() {
    string input;
    vector<string> vet;
    vector<string> original_input;
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
    for(int i=0; i<vet.size(); i++) {
        original_input.push_back(vet[i]);
    }
    vector<vector<Item>> final_result = rotate(vet);
    
    //sort strings that start with small letter
    sort(final_result[0].begin(), final_result[0].end(), compare_result);
    
    //sort strings that start with capital letter
    sort(final_result[1].begin(), final_result[1].end(), compare_result);
    
    cout << endl;
    
    final_result[0].insert(final_result[0].end(), final_result[1].begin(), final_result[1].end());
    vector<Item> vet1 = final_result[0];
    vector<string> rectangle1;
    vector<string> rectangle2;
    string spacer(5, ' ');
    
    for(string::size_type i=0; i != vet1.size(); i++) {
        // this will tell us where to break the setence into two parts, separated by space for debugging purposes
        int end = vet1[i].idx;
        // "I am a god" ===> "I am" and "a god" provided that the index is idx number 2
        vector<string> tmp_store = split(original_input[vet1[i].line]); // retrieve by the line number, either first line or second line in the given e.g.
        string tmp_str;
        for(int i=0; i<end; i++) {
            cout << tmp_store[i] << " ";
            tmp_str += tmp_store[i];
            if (i != end-1) tmp_str += " "; //concatenate each word follow by a space except for the last word
        }
        rectangle1.push_back(tmp_str); //get the first part before the space, for e.g. "I am"
        tmp_str = ""; // reset the tmp_str to empty string
        cout << spacer;
        for(int i=end; i<tmp_store.size(); i++) {
            cout << tmp_store[i] << " ";
            tmp_str += tmp_store[i];
            if (i != tmp_store.size()-1) tmp_str += " ";  //concatenate each word follow by a space except for the last word
        }
        rectangle2.push_back(tmp_str); // get the second part after the space for e.g. "a god"
        cout << endl;
    }
    cout << endl;
    vector<string> holder1 = frame(rectangle1, true); // decorate the first part of all the sentences with *
    vector<string> holder2 = frame(rectangle2, false);// decorate the second part of all the sentences with *
    vector<string> outcome = hcat(holder1, holder2); // horizontally concatenate the two frames
    printVector(outcome); //print the final output string
    cout << endl;
}
