#ifndef GRADESYSTEM_H
#define GRADESYSTEM_H

#include "Student.h"
#include <unordered_map>
#include <vector>
#include <string>

class GradeSystem { //manage all students & their grades
private:
   std::unordered_map<int, Student> students; //hash map to provide fast access/search

public:
    void addStudent(int id, const std::string& name, const std::vector<float>& grades); //add new student
    bool removeStudent(int id); //remove existed student
    Student* searchStudent(int id); //search for existed student
    bool updateGrades(int id, const std::vector<float>& grades); //update grades of specific student
    std::vector<Student> getAllStudents() const; //return all existed students
    std::vector<Student> sortByGPA() const; //return sudents sorted by GPA
    Student* showTopStudent(); //student with highest GPA
    bool isEmpty() const; //check whether there're students
};

#endif