#ifndef ADMINFUNCTIONALITY_H
#define ADMINFUNCTIONALITY_H

#include <QDialog>

namespace Ui {
class AdminFunctionality;
}

class AdminFunctionality : public QDialog
{
    Q_OBJECT

public:
    explicit AdminFunctionality(QWidget *parent = nullptr);
    ~AdminFunctionality();

private slots:


    void on_pushButton_clicked();



    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::AdminFunctionality *ui;
};

#endif // ADMINFUNCTIONALITY_H
