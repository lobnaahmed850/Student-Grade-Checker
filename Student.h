#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>

//student record in grading system
class Student {
private:
    int id;
    std::string name;
    std::vector<float> grades;
    float gpa;

public:
    Student();
    Student(int id, std::string name, std::vector<float> grades);
    void calculateGPA(); //GPA is average of all grades
    int getID() const;
    std::string getName() const;
    std::vector<float> getGrades() const;
    float getGPA() const;
    void setName(std::string name);
    void setGrades(std::vector<float> grades);
    std::string toString() const; //formatted string of student record
};

#endif