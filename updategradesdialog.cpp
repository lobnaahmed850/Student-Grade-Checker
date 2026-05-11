#include "updategradesdialog.h"
#include "ui_updategradesdialog.h"
#include <QStringList>

UpdateGradesDialog::UpdateGradesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateGradesDialog)
{
    ui->setupUi(this);
}

UpdateGradesDialog::~UpdateGradesDialog()
{
    delete ui;
}

int UpdateGradesDialog::getID() const {
    return ui->idInput->text().toInt();
}

std::vector<float> UpdateGradesDialog::getGrades() const {
    std::vector<float> grades;
    QString raw = ui->gradesInput->text();
    QStringList parts = raw.split(",");
    for (QString& part : parts) {
        bool ok;
        float grade = part.trimmed().toFloat(&ok);
        if (ok) grades.push_back(grade);
    }
    return grades;
}

bool UpdateGradesDialog::validateInput() {
    bool idOk;
    ui->idInput->text().toInt(&idOk);
    if (!idOk || ui->idInput->text().isEmpty()) {
        ui->errorLabel->setText("Invalid ID.");
        return false;
    }

    std::vector<float> grades = getGrades();
    if (grades.empty()) {
        ui->errorLabel->setText("Enter at least one grade.");
        return false;
    }

    for (float g : grades) {
        if (g < 0 || g > 100) {
            ui->errorLabel->setText("Each grade must be between 0 and 100.");
            return false;
        }
    }

    ui->errorLabel->clear();
    return true;
}

void UpdateGradesDialog::on_confirmBtn_clicked() {
    if (validateInput())
        accept();
}

void UpdateGradesDialog::on_cancelBtn_clicked() {
    reject();
}
