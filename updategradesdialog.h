#ifndef UPDATEGRADESDIALOG_H
#define UPDATEGRADESDIALOG_H

#include <QDialog>
#include <vector>

namespace Ui {
class UpdateGradesDialog;
}

class UpdateGradesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateGradesDialog(QWidget *parent = nullptr);
    ~UpdateGradesDialog();
    int getID() const;
    std::vector<float> getGrades() const;

private slots:
    void on_confirmBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::UpdateGradesDialog *ui;
    bool validateInput(); //validate input before accepting
};

#endif // UPDATEGRADESDIALOG_H
