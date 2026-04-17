#ifndef CASTVOTE_H
#define CASTVOTE_H

#include <QDialog>
#include <QString>
#include <QSqlTableModel>
namespace Ui {
class castVote;
}

class castVote : public QDialog
{
    Q_OBJECT

public:
    explicit castVote(const QString &VoterId, QWidget *parent = nullptr);
    ~castVote();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::castVote *ui;
     QString m_voterId;
    QSqlTableModel *model;
};

#endif // CASTVOTE_H
