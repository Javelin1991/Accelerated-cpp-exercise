#ifndef GUARD_GRADE_H
#define GUARD_GRADE_H

//grade.h
#include <vector>
#include "Student_Info.hpp"

double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double grade(const Student_info&);

#endif // GUARD_GRADE_H
