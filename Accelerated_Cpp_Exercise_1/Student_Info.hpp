#ifndef GUARD_STUDENT_INFO_H
#define GUARD_STUDENT_INFO_H

// Student_info.h
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <numeric>

using std::istream;
using std::ostream;
using std::vector;
using std::string;

struct Student_info
{
    std::string name;
    double midterm, final;
    std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);
bool did_all_hw(const Student_info& s);
double median(std::vector<double> vec);
double median_analysis(const std::vector<Student_info>& students);
void write_analysis(ostream& out, const string& name,
                    double analysis(const vector<Student_info>&),
                    const vector<Student_info>& did,
                    const vector<Student_info>& didnt);
double optimistic_median(const Student_info& s);
double optimistic_median_analysis(const vector<Student_info>& students);
double average_analysis(const vector<Student_info>& students);

#endif // GUARD_STUDENT_INFO_H
