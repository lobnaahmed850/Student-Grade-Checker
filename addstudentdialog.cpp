#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"
#include <QStringList>

AddStudentDialog::AddStudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddStudentDialog)
{
    ui->setupUi(this);
}

AddStudentDialog::~AddStudentDialog() //free UI elements when window closed
{
    delete ui;
}

int AddStudentDialog::getID() const {
    return ui->idInput->text().toInt(); //convert ID from string to int
}

std::string AddStudentDialog::getName() const {
    return ui->nameInput->text().toStdString(); //convert from QString to std::string
}

std::vector<float> AddStudentDialog::getGrades() const { //convert comma separated grades into float vector
    std::vector<float> grades;
    QString raw = ui->gradesInput->text();
    QStringList parts = raw.split(",");
    for (QString& part : parts) {
        bool ok;
        float grade = part.trimmed().toFloat(&ok); //trim spaces then convert
        if (ok) grades.push_back(grade);
    }
    return grades;
}

bool AddStudentDialog::validateInput() {
    bool idOk; //check ID
    ui->idInput->text().toInt(&idOk);
    if (!idOk || ui->idInput->text().isEmpty()) {
        ui->errorLabel->setText("Invalid ID.");
        return false;
    }

    if (ui->nameInput->text().trimmed().isEmpty()) { //check name not a blank or fill with spaces only
        ui->errorLabel->setText("Name can't be empty.");
        return false;
    }

    std::vector<float> grades = getGrades(); //check grades no across courses no
    int expected = ui->coursesSpinBox->value();
    if ((int)grades.size() != expected) {
        ui->errorLabel->setText(
            QString("Enter exactly %1 grades.").arg(expected));
        return false;
    }
    for (float g : grades) { //check grade range
        if (g < 0 || g > 100) {
            ui->errorLabel->setText("Each grade must be between 0 and 100.");
            return false;
        }
    }

    ui->errorLabel->clear(); //clear any previous error message
    return true;
}

void AddStudentDialog::on_confirmBtn_clicked() {
    if (validateInput())
        accept(); //built in function in QDialong
}

void AddStudentDialog::on_cancelBtn_clicked() {
    reject();
}


