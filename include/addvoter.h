#ifndef ADDVOTER_H
#define ADDVOTER_H

#include <QDialog>
#include <QSqlTableModel>
namespace Ui {
class addvoter;
}

class addvoter : public QDialog
{
    Q_OBJECT

public:
    explicit addvoter(QWidget *parent = nullptr);
    ~addvoter();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addvoter *ui;
     QSqlTableModel *model;
};

#endif // ADDVOTER_H
