//
//  extract_fails.cpp
//  Accelerated_Cpp_Exercise_1
//
//  Created by HTET NAING on 2/26/19.
//  Copyright © 2019 com.Javelin. All rights reserved.
//

#include "extract_fails.hpp"
#include "grade.hpp"
#include <list>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <vector>

//predicate to determine whether a student passed
bool pgrade(const Student_info& s)
{
    return !fgrade(s);
}

//predicate to determine whether a student failed
bool fgrade(const Student_info& s) {
    return grade(s) < 60;
}

// separate passing and failing student records
// version 4: use list instead of vector (essentially the same as version 3 otherwise)
// (S5.5/85)
std::list<Student_info> extract_fails(std::list<Student_info>& students)
{
    std::list<Student_info> fail;
    std::list<Student_info>::iterator iter = students.begin();
    while (iter != students.end())
    {
        if (fgrade(*iter))
        {
            fail.push_back(*iter);
            iter = students.erase(iter);
        }
        else
            ++iter;
    }
    return fail;
}

// two pass solution
vector<Student_info>
extract_fails_v2(vector<Student_info>& students) {
    vector<Student_info> fail;
    remove_copy_if(students.begin(), students.end(),
                   back_inserter(fail), pgrade);
    students.erase(remove_if(students.begin(), students.end(),fgrade), students.end());
    return fail;
}

vector<Student_info>
extract_fails_v3(vector<Student_info>& students)
{
    vector<Student_info>::iterator iter =
    stable_partition(students.begin(), students.end(), pgrade);
    vector<Student_info> fail(iter, students.end());
    students.erase(iter, students.end());
    return fail;
}
