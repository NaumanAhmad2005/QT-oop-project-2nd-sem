#ifndef VOTERLOGINDAMN_H
#define VOTERLOGINDAMN_H

#include <QDialog>

namespace Ui {
class voterlogindamn;
}

class voterlogindamn : public QDialog
{
    Q_OBJECT

public:
    explicit voterlogindamn(QWidget *parent = nullptr);
    ~voterlogindamn();

private slots:
    void on_pushButton_clicked();

private:
    Ui::voterlogindamn *ui;
};

#endif // VOTERLOGINDAMN_H
