#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GradeSystem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    //declaring functions for created buttons
    void on_addStudentBtn_clicked();
    void on_removeStudentBtn_clicked();
    void on_searchStudentBtn_clicked();
    void on_displayAllBtn_clicked();
    void on_sortByGPABtn_clicked();
    void on_showTopStudentBtn_clicked();
    void on_updateGradesBtn_clicked();


private:
    Ui::MainWindow *ui;
    GradeSystem gradeSystem;
    //helpers
    void refreshTable(const std::vector<Student>& students);
    void updateStatusLabel();
    QString letterGrade(float gpa); //convert GPA to letter grade
};
#endif // MAINWINDOW_H
