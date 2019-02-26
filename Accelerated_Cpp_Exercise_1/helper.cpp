//
//  print.cpp
//  Accelerated_Cpp_Exercise_1
//
//  Created by HTET NAING on 2/26/19.
//  Copyright © 2019 com.Javelin. All rights reserved.
//

#include "helper.hpp"
#include "grade.hpp"
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include "Student_Info.hpp"
#include <iomanip>

using std::list; using std::streamsize; using std::string;
using std::cout; using std::endl; using std::setprecision; using std::vector;

void print(std::list<Student_info>& students, int maxlen) {
    for (list<Student_info>::const_iterator i = students.begin();
         i != students.end(); ++i) {
        cout << i->name
        << string(maxlen + 1 - i->name.size(), ' ');
        
        //compute and write the grade
        try
        {
            double final_grade = grade(*i);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
            << setprecision((int) prec);
        }
        catch (std::domain_error e)
        {
            cout << e.what();
        }
        cout << endl;
    }
}

vector<string> split(const string& s) {
    vector<string> vet;
    typedef string::size_type string_size;
    string_size i = 0;
    
    while(i != s.size()) {
            while( i != s.size() && isspace(s[i])) {
                i++;
            }
        
            string_size j = i;
            while (j != s.size() && !isspace(s[j])) {
                j++;
            }
            
            if (i != j) {
                //substr selects [x, y)
                vet.push_back(s.substr(i, j-i));
                i = j;
            }
    }
    return vet;
}
