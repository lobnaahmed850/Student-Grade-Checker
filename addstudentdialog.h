#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>
#include <vector>
#include <string>

namespace Ui {
class AddStudentDialog;
}

class AddStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudentDialog(QWidget *parent = nullptr); //constructor
    ~AddStudentDialog(); //destructor
    //some getters for returning student info
    int getID() const;
    std::string getName() const;
    std::vector<float> getGrades() const;

private slots:
    void on_confirmBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::AddStudentDialog *ui;
     bool validateInput(); //validate user input fields
};

#endif // ADDSTUDENTDIALOG_H
