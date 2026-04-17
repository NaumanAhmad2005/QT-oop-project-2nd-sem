#ifndef VOTERFUNCTIONALITY_H
#define VOTERFUNCTIONALITY_H

#include <QDialog>
#include <QString>
namespace Ui {
class voterfunctionality;
}

class voterfunctionality : public QDialog
{
    Q_OBJECT

public:
    explicit voterfunctionality(const QString &voterid ,QWidget *parent = nullptr);
    ~voterfunctionality();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::voterfunctionality *ui;
    QString m_voterId;
};

#endif // VOTERFUNCTIONALITY_H
