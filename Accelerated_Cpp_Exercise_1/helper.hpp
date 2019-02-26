//
//  print.hpp
//  Accelerated_Cpp_Exercise_1
//
//  Created by HTET NAING on 2/26/19.
//  Copyright © 2019 com.Javelin. All rights reserved.
//

#ifndef print_hpp
#define print_hpp

#include <stdio.h>
#include <list>
#include <string>
#include "Student_Info.hpp"

using std::string; using std::vector;

void print(std::list<Student_info>&, int);
vector<string> split(const string&);
#endif /* print_hpp */
