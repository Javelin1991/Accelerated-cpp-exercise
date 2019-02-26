#include "Student_Info.hpp"

using std::istream;
using std::vector;

// we are interested in sorting the Student_info object by the student's name
bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

// read student's name, midterm exam grade, final exam grade, and homework grades
// and store into the Student_info object
// (as defined in S4.2.2/62)
istream& read(istream& is, Student_info& s)
{
    // read and store the student's name and midterm and final exam grades
    is >> s.name >> s.midterm >> s.final;
    
    // read and store all the student's homework grades
    return is;
}

// read homework grades from an input stream into a vector<double>
// (as defined in S4.1.3/57)
istream& read_hw(istream& in, vector<double>& hw)
{

        // get rid of previous contents
        hw.clear();
        
        // read homework grades
        double x;
        while (in >> x)
            hw.push_back(x);
        
        // clear the stream so that input will work for the next student
        in.clear();
    return in;
}
