# Student Grade Checker

A desktop application built with **C++** and **Qt Framework** for storing, managing, and analyzing student grade records.

---

## Group Members

| Name | ID |
|------|----|
| Lobna Ahmed Abd Elhamid | 2300360 |
| Adham Khaled Mohamed Saada | 2300191 |
| Abdelrahman Zakaria Talaat | 2300163 |

---

## Project Description

Student Grade Checker is a GUI-based desktop application that allows users to manage student academic records efficiently. The system supports adding students, updating grades, searching records, sorting by GPA, and displaying top student - all through a clean Qt interface backed by a C++ data management system.

---

## Project Structure

```
StudentGradeChecker/
├── main.cpp                   # Qt application entry point
├── Student.h / .cpp           # Student record class
├── GradeSystem.h / .cpp       # Backend data management
├── mainwindow.h / .cpp / .ui  # Main window UI and logic
├── addstudentdialog.h / .cpp / .ui      # Add student popup dialog
├── updategradesdialog.h / .cpp / .ui    # Update grades popup dialog
└── CMakeLists.txt             # Qt build configuration
```

---

## Data Structures Used

| Data Structure | Location | Why It Was Chosen |
|----------------|----------|--------------------|
| `unordered_map<int, Student>` | `GradeSystem::students` | O(1) average insert, search, and delete by student ID - fastest for key-based lookup |
| `vector<float>` | `Student::grades` | Variable-length grades per student - size is only known at runtime, supports dynamic resizing |
| `vector<Student>` | `getAllStudents()`, `sortByGPA()` | Temporary collection for display and sorting - supports random access and std::sort |
| `std::string` | `Student::name`, `toString()` | Variable-length text storage for names and formatted output |

---

## Implemented Features

- **Add Student** - Enter ID, name, number of courses, and grades via popup dialog
- **Remove Student** - Select a row from the table and remove with confirmation
- **Search Student** - Search by student ID and display matching record in table
- **Update Grades** - Replace a student's grades and automatically recalculate GPA
- **Display All Students** - Show all records in a structured table with ID, Name, Grades, GPA, and Letter Grade
- **Sort by GPA** - Sort all students in descending GPA order
- **Show Top Student** - Display the student with the highest GPA in a popup
- **Input Validation** - All dialogs validate input and show inline error messages
- **Status Bar** - Shows total student count at all times
-
- **Letter Grade** — Automatically assigns A/B/C/D/F based on GPA

---

## How to Compile and Run

### Requirements

- Qt 6.x or Qt 5.15+
- Qt Creator IDE 
- CMake 3.16+
- C++17 compatible compiler (GCC / MSVC / Clang)

### Steps - Qt Creator 

```
1. Open Qt Creator
2. File → Open Project → select CMakeLists.txt
3. Configure the project with your Qt kit
4. Click the green Run button (Ctrl + R)
```

### Steps — Command Line (CMake)

```bash
# 1. Clone the repository
git clone https://github.com/lobnaahmed850/Student-Grade-Checker.git
cd Student-Grade-Checker

# 2. Create build directory
mkdir build && cd build

# 3. Configure with CMake
cmake .. -DCMAKE_PREFIX_PATH=C:\Qt\6.11.0\mingw_64\lib\cmake

# 4. Build
cmake --build .

# 5. Run
./Student-Grade-Checker        # Linux / macOS
Student-Grade-Checker.exe      # Windows
```

---

## How to Test the Application

1. Launch the application
2. Click **Add Student** → Enter: ID `1001`, Name `Ahmed Ali`, Courses `4`, Grades `90, 85, 78, 92`
3. Add more students with different GPAs
4. Use **Search** to find a student by ID
5. Click **Sort by GPA** to order students
6. Select a row and click **Remove Student**
7. Click **Top Student** to see the highest-performing student
8. Click **Update Grades** → enter an existing ID and new grades

---

## AI Usage Declaration

AI tools were used during this project strictly as a development assistant.
All final decisions, implementations, and understanding remain with the group.

### Tools Used

| AI Tool | Purpose |
|---------|---------|
| Claude (Anthropic) | Feature recommendations, code review, test design, documentation |

---

### What AI Was Used For

| Area | Details |
|------|---------|
| Feature recommendations | Asked AI to suggest which functions are commonly expected in a grade management system (e.g. `sortByGPA`, `showTopStudent`, `searchStudent`). Group evaluated and selected what was appropriate for the project scope. |
| Test scenario design | AI suggested a structured test plan covering happy path, edge cases, duplicate IDs, and invalid input. Group executed all tests manually and verified results. |
| Documentation assistance | AI helped writing readme file based on group description for the implemented project. |

---

### What Was Modified or Rejected

| AI Suggestion | Action Taken |
|---------------|--------------|
| Suggested keeping `showStatistics()`, `saveToFile()`, `loadFromFile()` functions | **Rejected** — group decided to keep the scope focused on core features for this submission |
| Recommended using `priority_queue` to maintain top student in O(1) | **Reviewed but not adopted** — group understood the concept but kept linear scan `O(n)` for simplicity and readability at this stage |

---

This demonstrated that AI output must always be tested and verified,
not copied directly into a project.

---

### What the Group Understood and Implemented Themselves

- The full class design for `Student`, `GradeSystem`, `MainWindow`,
  `AddStudentDialog`, and `UpdateGradesDialog`
- Why `unordered_map` was chosen over other containers for O(1) student lookup
- How Qt signals and slots connect the GUI buttons to backend logic
- Manual execution and verification of all test cases

---

> Using AI as an assistant does not replace understanding.
> Every AI suggestion was evaluated, tested, and either adopted, modified, or rejected by the group.

---

## License

This project was developed as an academic assignment. All rights reserved by the group members.
