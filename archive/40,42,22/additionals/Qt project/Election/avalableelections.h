#ifndef AVALABLEELECTIONS_H
#define AVALABLEELECTIONS_H

#include <QDialog>
#include <QSqlTableModel>
namespace Ui {
class avalableelections;
}

class avalableelections : public QDialog
{
    Q_OBJECT

public:
    explicit avalableelections(QWidget *parent = nullptr);
    ~avalableelections();

private slots:
    void on_pushButton_clicked();

private:
    Ui::avalableelections *ui;
    QSqlTableModel *model;
};

#endif // AVALABLEELECTIONS_H
