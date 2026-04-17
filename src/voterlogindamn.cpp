#include "voterlogindamn.h"
#include "ui_voterlogindamn.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "UserManager.h"
#include "voterfunctionality.h"
voterlogindamn::voterlogindamn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::voterlogindamn)
{
    ui->setupUi(this);
}

voterlogindamn::~voterlogindamn()
{
    delete ui;
}

void voterlogindamn::on_pushButton_clicked()
{
    if (!DatabaseManager::instance().connect()) {
        QMessageBox::critical(this, "Database Error", "Could not connect to database.");
        return;
    }
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    UserManager damn;
    if(damn.authenticateVoter(username, password)){
        QSqlQuery query(DatabaseManager::instance().getDatabase());
        query.prepare("SELECT id FROM voters WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        QString voterId;

        if (query.exec() && query.next()) {
            voterId = query.value(0).toString();

            voterfunctionality *Vf = new voterfunctionality(voterId);
            Vf->show();
            this->close();
        }
    }
    else{
        QMessageBox::warning(this, "title", "Not ok");
    }
}

