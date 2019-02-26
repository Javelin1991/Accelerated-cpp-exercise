#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.hpp"
#include "Student_info.hpp"

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

int main()
{
    vector<Student_info> students;
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
        double x;
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

    // alphabetize the student records
    sort(students.begin(), students.end(), compare);

    // write the names and grades
    for (vector<Student_info>::size_type i = 0;
         i != students.size(); ++i)
    {
        //write the name, padded on teh right to maxlen + 1 characters
        cout << students[i].name
             << string(maxlen + 1 - students[i].name.size(), ' ');

         //compute and write the grade
        try
        {
            double final_grade = grade(students[i]);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec);
        }
        catch (domain_error e)
        {
            cout << e.what();
        }
        cout << endl;
    }
    return 0;
}
