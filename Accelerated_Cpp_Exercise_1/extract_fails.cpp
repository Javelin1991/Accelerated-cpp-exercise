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
