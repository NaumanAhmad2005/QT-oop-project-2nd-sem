#include "adminfunctionality.h"
#include "ui_adminfunctionality.h"
#include "createelction.h"
#include "createcandidatedamn.h"
#include "QDebug"
#include "addvoter.h"
#include "viewresults.h"
#include "mainwindow.h"
AdminFunctionality::AdminFunctionality(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminFunctionality)
{
    ui->setupUi(this);

}

AdminFunctionality::~AdminFunctionality()
{
    delete ui;
}




void AdminFunctionality::on_pushButton_clicked()
{
    createElction *damnele = new createElction();
    damnele->show();
    this->close();
}



void AdminFunctionality::on_pushButton_2_clicked()
{
    CreateCandidatedamn *CC = new CreateCandidatedamn();

    CC->show();
this->close();
}


void AdminFunctionality::on_pushButton_3_clicked()
{
    addvoter *av = new addvoter();
    av->show();
    this->close();
}


void AdminFunctionality::on_pushButton_4_clicked()
{
    viewResults *vh = new viewResults();
    vh->show();
    this->close();
}


void AdminFunctionality::on_pushButton_5_clicked()
{
    MainWindow *MW = new MainWindow();
    MW->show();
    this->close();
}

