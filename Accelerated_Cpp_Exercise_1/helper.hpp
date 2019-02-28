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

using std::string; using std::vector; using std::list;

struct Item
{
    std::string name;
    int idx;
    int line;
};

void print(list<Student_info>&, int);
vector<string> hcat(const vector<string>& left, const vector<string>&);
vector<string> vcat(const vector<string>& top, const vector<string>&);
vector<string> split(const string&);
vector<string> frame(const vector<string>&, bool);
vector<Item> frameItem(const vector<Item>&);
void printVector(const vector<string>&);
string rotateLeft(vector<string>&);
vector<vector<Item>> rotate(vector<string>&);
bool compare_result(const Item&, const Item&);

#endif /* print_hpp */
