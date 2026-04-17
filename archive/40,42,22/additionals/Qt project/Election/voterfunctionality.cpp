#include "voterfunctionality.h"
#include "ui_voterfunctionality.h"
#include "castvote.h"
#include <avalableelections.h>
#include "mainwindow.h"
voterfunctionality::voterfunctionality(const QString &voterId, QWidget *parent)
    : QDialog(parent), ui(new Ui::voterfunctionality), m_voterId(voterId)
{
    ui->setupUi(this);
}
voterfunctionality::~voterfunctionality()
{
    delete ui;
}

void voterfunctionality::on_pushButton_clicked()
{
    castVote *CV = new castVote(m_voterId);
    CV->show();
    this->close();
}


void voterfunctionality::on_pushButton_2_clicked()
{
    avalableelections *AE = new avalableelections();
    AE->show();
    this->close();
}


void voterfunctionality::on_pushButton_3_clicked()
{
    MainWindow *MW = new MainWindow();
    MW->show();
    this->close();
}

