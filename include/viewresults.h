#ifndef VIEWRESULTS_H
#define VIEWRESULTS_H

#include <QDialog>
#include <QSqlQueryModel>
namespace Ui {
class viewResults;
}

class viewResults : public QDialog
{
    Q_OBJECT

public:
    explicit viewResults(QWidget *parent = nullptr);
    ~viewResults();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::viewResults *ui;
    QSqlQueryModel *model = nullptr;
};

#endif // VIEWRESULTS_H
