#include "GradeSystem.h"
#include <algorithm>
using namespace std;

//insert new student to hash map with ID as key
void GradeSystem::addStudent(int id, const string& name, const vector<float>& grades) {
    if (students.find(id) != students.end()) return;  //ID already exists, skip
    students[id] = Student(id, name, grades); //average insertion
}

bool GradeSystem::removeStudent(int id) {
    return students.erase(id) > 0;
}

Student* GradeSystem::searchStudent(int id) {
    auto it = students.find(id); //average search
    if (it != students.end()) return &it->second;
    return nullptr;
}

bool GradeSystem::updateGrades(int id, const vector<float>& grades) {
    auto it = students.find(id);
    if (it == students.end()) return false;
    it->second.setGrades(grades);
    return true;
}

vector<Student> GradeSystem::getAllStudents() const { //copies students from hash map into vector
    vector<Student> result;
    for (const auto& pair : students)
        result.push_back(pair.second); //pair.second = Student
    return result;
}

vector<Student> GradeSystem::sortByGPA() const {
    vector<Student> temp = getAllStudents();
    sort(temp.begin(), temp.end(), [](const Student& a, const Student& b) { //sort with lambda comparator
        return a.getGPA() > b.getGPA();
    });
    return temp;
}

Student* GradeSystem::showTopStudent() {
    if (students.empty()) return nullptr;
    auto top = students.begin(); //assume top is first
    for (auto it = students.begin(); it != students.end(); ++it)
        if (it->second.getGPA() > top->second.getGPA())
            top = it;
    return &top->second;
}

bool GradeSystem::isEmpty() const {
    return students.empty();
}