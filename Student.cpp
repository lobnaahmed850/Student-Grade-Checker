#include "Student.h"
#include <iomanip>
#include <sstream>
using namespace std;

Student::Student() {
    id = 0;
    name = "Unknown";
    gpa = 0;
}

Student::Student(int id, string name, vector<float> grades) {
    this->id = id;
    this->name = name;
    this->grades = grades;
    calculateGPA(); //calculate GPA immediately :D
}

void Student::calculateGPA() { //GPA is mean of all grades
    if (grades.empty()) {
        gpa = 0;
        return;
    }
    float sum = 0;
    for (float grade : grades) {
        sum += grade;
    }
    gpa = sum / grades.size();
}

int Student::getID() const {
    return id;
}

string Student::getName() const {
    return name;
}

vector<float> Student::getGrades() const {
    return grades;
}

float Student::getGPA() const {
    return gpa;
}

void Student::setName(string name) {
    this->name = name;
}

void Student::setGrades(vector<float> grades) {
    this->grades = grades;
    calculateGPA(); //GPA synchronize with new grades ^_^
}

string Student::toString() const { //formatted string for display
    ostringstream oss;
    oss << "ID: "     << id     << "\n"
        << "Name: "   << name   << "\n"
        << "Grades: ";
    for (float g : grades) oss << g << " ";
    oss << "\nGPA: "  << fixed << setprecision(2) << gpa;
    return oss.str();
}
