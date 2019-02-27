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

string::size_type width(const vector<string>& v) {
    string::size_type maxlen = 0;
    for(vector<string>::size_type i=0; i != v.size(); i++) {
        maxlen = max(maxlen, v[i].size());
    }
    return maxlen;
}

vector<string> frame(const vector<string>& v) {
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');
    
    ret.push_back(border);
    
    for(vector<string>::size_type i=0; i != v.size(); i++) {
        ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ') + " *");
    }
    ret.push_back(border);
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

vector<string> rotate(vector<string>& vec) {
    vector<string> final_result;
    int k = 0;
    while(k < vec.size()) {
        string temp = vec[k];
        final_result.push_back(temp);
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
            final_result.push_back(final_string);
        }
        k++;
    }
    sort(final_result.begin(), final_result.end());
    return final_result;
}




