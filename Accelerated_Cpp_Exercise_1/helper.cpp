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

using std::list; using std::streamsize; using std::string; using std::max; using std::sort;
using std::cout; using std::endl; using std::setprecision; using std::vector; using std::isupper;

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

string::size_type width(const vector<string>& v) {
    string::size_type maxlen = 0;
    for(vector<string>::size_type i=0; i != v.size(); i++) {
        maxlen = max(maxlen, v[i].size());
    }
    return maxlen;
}

string::size_type item_width(const vector<Item>& v) {
    string::size_type maxlen = 0;
    for(vector<Item>::size_type i=0; i != v.size(); i++) {
        maxlen = max(maxlen, v[i].name.size());
    }
    return maxlen;
}

vector<string> frame(const vector<string>& v, bool hug_right) {
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');
    
    ret.push_back(border);
    
    for(vector<string>::size_type i=0; i != v.size(); i++) {
        if (hug_right) {
            ret.push_back("* " + string(maxlen - v[i].size(), ' ') + v[i] + " *");
        } else {
            ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");
        }
    }
    ret.push_back(border);
    return ret;
}

vector<Item> frameItem(const vector<Item>& v) {
    vector<Item> ret;
    string::size_type maxlen = item_width(v);
    string border(maxlen + 4, '*');
    Item tmp;
    tmp.name = border;
    ret.push_back(tmp);
    
    for(vector<Item>::size_type i=0; i != v.size(); i++) {
        Item tmp2;
        tmp2.idx = v[i].idx;
        tmp2.name = "* " + v[i].name + string(maxlen - v[i].name.size(), ' ') + " *";
        ret.push_back(tmp2);
    }
    Item tmp3;
    tmp3.name = border;
    ret.push_back(tmp3);
    return ret;
}

vector<string> vcat(const vector<string>& top, const vector<string>& bottom) {
    vector<string> ret = top;
    ret.insert(ret.end(), bottom.begin(), bottom.end());
    return ret;
}

vector<string> hcat(const vector<string>& left, const vector<string>& right) {
    vector<string> ret;
    
    string::size_type width1 = width(left) + 1;
    
    vector<string>::size_type i = 0, j = 0;
    while(i != left.size() || j != right.size()) {
        string s;
        
        if (i != left.size()) {
            s = left[i++];
        }
        
        s += string(width1 - s.size(), ' ');
        
        if (j != right.size()) {
            s += right[j++];
        }
        ret.push_back(s);
    }
    return ret;
}

void printVector(const vector<string>& vet) {
    for(string::size_type i = 0; i != vet.size(); i++) {
        cout << vet[i] << endl;
    }
}

string rotateLeft(vector<string>& vec) {
    string result;
    
    for(string::size_type i=0; i<vec.size()-1; i++) {
        result += (vec[i] + " ");
    }
    result += vec[vec.size()-1];
    return result;
}

bool compare_result(const Item& x,const Item& y)
{
    return x.name < y.name;
}

vector<vector<Item>> rotate(vector<string>& vec) {
    vector<Item> final_result_upper;
    vector<Item> final_result_lower;
    vector<vector<Item>> final_result;
    int k = 0;
    while(k < vec.size()) {
        string temp = vec[k];
        Item new_item;
        new_item.line = k;
        new_item.name = temp;
        new_item.idx = 0;
        if (isupper(temp[0])) {
            final_result_upper.push_back(new_item);
        } else {
            final_result_lower.push_back(new_item);
        }
        vector<string> split_string = split(temp);
        
        for(int i=0; i<split_string.size()-1; i++) {
            string::size_type j = 1;
            string temp = split_string[0];
            
            while(j < split_string.size()) {
                split_string[j-1] = split_string[j];
                j++;
            }
            split_string[split_string.size()-1] = temp;
            string final_string = rotateLeft(split_string);
            Item tmp_item;
            tmp_item.line = k;
            tmp_item.idx = i+1;
            tmp_item.name = final_string;
            
            if (isupper(final_string[0])) {
                final_result_upper.push_back(tmp_item);
            } else {
                final_result_lower.push_back(tmp_item);
            }
        }
        k++;
    }
    final_result.push_back(final_result_lower);
    final_result.push_back(final_result_upper);
    return final_result;
}




