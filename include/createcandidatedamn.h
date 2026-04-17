#ifndef CREATECANDIDATEDAMN_H
#define CREATECANDIDATEDAMN_H

#include <QDialog>
#include <QSqlTableModel>
namespace Ui {
class CreateCandidatedamn;
}

class CreateCandidatedamn : public QDialog
{
    Q_OBJECT

public:
    explicit CreateCandidatedamn(QWidget *parent = nullptr);
    ~CreateCandidatedamn();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CreateCandidatedamn *ui;
    QSqlTableModel *model;
};

#endif // CREATECANDIDATEDAMN_H
