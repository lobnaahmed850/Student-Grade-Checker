#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addstudentdialog.h"
#include "updategradesdialog.h"
#include <QMessageBox>
#include <QString>
#include <sstream>
#include <iomanip>

//set up UI
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->studentsTable->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    refreshTable(gradeSystem.getAllStudents());
    updateStatusLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::letterGrade(float gpa) { //convert numeric GPA to letter grade
    if (gpa >= 90) return "A";
    if (gpa >= 80) return "B";
    if (gpa >= 70) return "C";
    if (gpa >= 60) return "D";
    return "F";
}

void MainWindow::refreshTable(const std::vector<Student>& students) { //called after each data change to keep UI synchronize with backend
    ui->studentsTable->setRowCount(0); //clear existing rows

    //draw rows in table
    for (const Student& s : students) {
        int row = ui->studentsTable->rowCount();
        ui->studentsTable->insertRow(row);

        //build grades string
        QString gradesStr;
        for (float g : s.getGrades())
            gradesStr += QString::number(g) + " ";

        //build GPA string
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << s.getGPA();

        //set student info in table
        ui->studentsTable->setItem(row, 0,
                                   new QTableWidgetItem(QString::number(s.getID())));
        ui->studentsTable->setItem(row, 1,
                                   new QTableWidgetItem(QString::fromStdString(s.getName())));
        ui->studentsTable->setItem(row, 2,
                                   new QTableWidgetItem(gradesStr.trimmed()));
        ui->studentsTable->setItem(row, 3,
                                   new QTableWidgetItem(QString::fromStdString(oss.str())));
        ui->studentsTable->setItem(row, 4,
                                   new QTableWidgetItem(letterGrade(s.getGPA())));
    }
}

void MainWindow::updateStatusLabel() { //update total students
    std::vector<Student> all = gradeSystem.getAllStudents();
    QString status = "Total Students: " + QString::number(all.size());
    ui->statusLabel->setText(status);
}

void MainWindow::on_addStudentBtn_clicked() {
    AddStudentDialog dialog(this); //open add student window

    if (dialog.exec() == QDialog::Accepted) { //input valid
        int   id     = dialog.getID();
        auto  name   = dialog.getName();
        auto  grades = dialog.getGrades();
        // check duplicate
        if (gradeSystem.searchStudent(id)) {
            QMessageBox::warning(this, "Duplicate",
                                 "Student with ID " + QString::number(id) + " already exists.");
            return;
        }

        gradeSystem.addStudent(id, name, grades);
        refreshTable(gradeSystem.getAllStudents());
        updateStatusLabel();
        QMessageBox::information(this, "Success", "Student added successfully!");
    }
}

void MainWindow::on_removeStudentBtn_clicked() {
    //get selected row
    int row = ui->studentsTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "No Selection",
                             "Please select a student row to remove.");
        return;
    }

    int id = ui->studentsTable->item(row, 0)->text().toInt(); //read ID from selected row

    auto reply = QMessageBox::question(this, "Confirm Remove",
                                       "Remove student with ID " + QString::number(id) + "?",
                                       QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        gradeSystem.removeStudent(id);
        refreshTable(gradeSystem.getAllStudents());
        updateStatusLabel();
    }
}

void MainWindow::on_searchStudentBtn_clicked() {
    QString text = ui->searchInput->text().trimmed();
    if (text.isEmpty()) {
        //empty search, show all
        refreshTable(gradeSystem.getAllStudents());
        return;
    }

    bool ok;
    int id = text.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input",
                             "Please enter a valid numeric ID.");
        return;
    }

    Student* s = gradeSystem.searchStudent(id);
    if (s) {
        //show only found student in table
        std::vector<Student> result = {*s};
        refreshTable(result);
    }
    else {
        QMessageBox::information(this, "Not Found",
                                 "No student found with ID " + QString::number(id));
        refreshTable(gradeSystem.getAllStudents());
    }
}

void MainWindow::on_updateGradesBtn_clicked() {
    UpdateGradesDialog dialog(this); //open update grade window

    if (dialog.exec() == QDialog::Accepted) {
        int  id     = dialog.getID();
        auto grades = dialog.getGrades();

        if (!gradeSystem.updateGrades(id, grades)) {
            QMessageBox::warning(this, "Not Found",
                                 "No student found with ID " + QString::number(id));
            return;
        }

        refreshTable(gradeSystem.getAllStudents());
        updateStatusLabel();
        QMessageBox::information(this, "Success", "Grades updated successfully!");
    }
}

void MainWindow::on_displayAllBtn_clicked() { //restore unfiltered students list
    ui->searchInput->clear();
    refreshTable(gradeSystem.getAllStudents());
    updateStatusLabel();
}

void MainWindow::on_sortByGPABtn_clicked() { //display student sorted by GPA descending
    std::vector<Student> sorted = gradeSystem.sortByGPA();
    if (sorted.empty()) {
        QMessageBox::information(this, "Empty", "No students to sort.");
        return;
    }
    refreshTable(sorted);
}

void MainWindow::on_showTopStudentBtn_clicked() { //find & display student with highest GPA
    Student* top = gradeSystem.showTopStudent();
    if (!top) {
        QMessageBox::information(this, "Empty", "No students available.");
        return;
    }
    //formatted message for popup
    QString msg =
        "ID: "+ QString::number(top->getID())+"\n" +
        "Name: "+ QString::fromStdString(top->getName())+"\n" +
        "GPA: "+ QString::number(top->getGPA(), 'f', 2)+"\n" +
        "Grade: "+ letterGrade(top->getGPA());

    QMessageBox::information(this, "Top Student", msg);
}
