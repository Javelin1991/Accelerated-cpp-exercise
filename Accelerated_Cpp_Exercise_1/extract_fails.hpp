//
//  extract_fails.hpp
//  Accelerated_Cpp_Exercise_1
//
//  Created by HTET NAING on 2/26/19.
//  Copyright © 2019 com.Javelin. All rights reserved.
//

#ifndef extract_fails_hpp
#define extract_fails_hpp

#include <stdio.h>
#include "Student_Info.hpp"
#include <list>

bool fgrade(const Student_info&);
std::list<Student_info> extract_fails(std::list<Student_info>&);
vector<Student_info> extract_fails_v2(vector<Student_info>& students);
vector<Student_info> extract_fails_v3(vector<Student_info>& students);
#endif /* extract_fails_hpp */
