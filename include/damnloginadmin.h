#ifndef DAMNLOGINADMIN_H
#define DAMNLOGINADMIN_H

#include <QDialog>

namespace Ui {
class damnLoginAdmin;
}

class damnLoginAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit damnLoginAdmin(QWidget *parent = nullptr);
    ~damnLoginAdmin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::damnLoginAdmin *ui;
};

#endif // DAMNLOGINADMIN_H
