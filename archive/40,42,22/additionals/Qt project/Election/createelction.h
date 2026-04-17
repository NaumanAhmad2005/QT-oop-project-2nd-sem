#ifndef CREATEELCTION_H
#define CREATEELCTION_H

#include <QDialog>
#include <QSqlTableModel>
namespace Ui {
class createElction;
}

class createElction : public QDialog
{
    Q_OBJECT

public:
    explicit createElction(QWidget *parent = nullptr);
    ~createElction();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::createElction *ui;
     QSqlTableModel *model;
};

#endif // CREATEELCTION_H
