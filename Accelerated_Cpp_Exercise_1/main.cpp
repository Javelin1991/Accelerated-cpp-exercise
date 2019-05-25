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
#include <map>

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
using std::map;

void runGradeCalculator();
void runGradeCalculator_v2();
void runStringSplitter();
void runStringFrameConcatenator();
void permutatePageIndex();
void checkPalindrome();
void findURLs();
void countWords();

int main()
{
    int programmeChoice;
    cout << "Choose which programme to run: " << endl;
    cout << "(1) Grade Calculator using mean" << endl;
    cout << "(2) Grade Calculator using median" << endl;
    cout << "(3) String Splitter" << endl;
    cout << "(4) String Frame Concatenator" << endl;
    cout << "(5) Rotate" << endl;
    cout << "(6) Check Palindrome" << endl;
    cout << "(7) URL String Finder" << endl;
    cout << "(8) Count words occurence" << endl;

    cin >> programmeChoice;
    
    switch (programmeChoice) {
        case 1:
            runGradeCalculator();
            break;
        case 2:
            runGradeCalculator_v2();
            break;
        case 3:
            runStringSplitter();
            break;
        case 4: runStringFrameConcatenator();
            break;
        case 5: permutatePageIndex();
            break;
        case 6: checkPalindrome();
            break;
        case 7: findURLs();
            break;
        case 8: countWords();
            break;
        default:
            cout << "Invalid Input. Please run the program again." << endl;
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

void runGradeCalculator_v2() {
    vector<Student_info> did, didnt;
    Student_info student;
    // read all the records, separating them based on whether all homework was done
    while (read(cin, student)) {
        if (did_all_hw(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }
    // check that both groups contain data
    if (did.empty()) {
        cout << "No student did all the homework!" << endl;
    }
    if (didnt.empty()) {
        cout << "Every student did all the homework!" << endl;
    }
    // do the analyses
    write_analysis(cout, "median", median_analysis, did, didnt);
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "median of homework turned in",
                   optimistic_median_analysis, did, didnt);
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
    getchar(); // to consume the dummy char in the buffer
    
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

void checkPalindrome() {
    getchar(); // to consume the dummy char in the buffer
    cout << "Please enter a string: ";
    string input;
    getline(cin, input);
    if (is_palindrome(input)) {
        cout << "The given word is a Palinrome!" << endl;
    } else {
        cout << "The given word is not a Palinrome!" << endl;
    }
}

void findURLs() {
    getchar(); // to consume the dummy char in the buffer
    cout << "Please enter a string: ";
    string input;
    getline(cin, input);

    vector<string> output = find_urls(input);
    printVector(output);
}

void countWords() {
    getchar(); // to consume the dummy char in the buffer
    cout << "Please provide input strings." << endl;
    cout << "Enter Ctrl + d to produce answer" << endl;

    string s;
    map<string, int> counters; // store each word and an associated counter
    // read the input, keeping track of each word and how often we see it
    while (cin >> s) {
        ++counters[s];
    }
    cout << endl;
    // write the words and associated counts
    for (map<string, int>::const_iterator it = counters.begin();
         it != counters.end(); ++it) {
        cout << it->first << "\t" << it->second << endl;
    }
}

