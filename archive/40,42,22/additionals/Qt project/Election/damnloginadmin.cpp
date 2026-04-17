#include "damnloginadmin.h"
#include "ui_damnloginadmin.h"
#include "QMessageBox"
#include "UserManager.h"
#include "adminfunctionality.h"
damnLoginAdmin::damnLoginAdmin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::damnLoginAdmin)
{
    ui->setupUi(this);
}

damnLoginAdmin::~damnLoginAdmin()
{
    delete ui;
}

void damnLoginAdmin::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    UserManager damnmanager;
    bool authent = damnmanager.authenticateAdmin(username.toStdString(), password.toStdString());

    if(authent){
        AdminFunctionality *func = new AdminFunctionality();
        func->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed",
                             "Invalid admin credentials!");
    }
}

