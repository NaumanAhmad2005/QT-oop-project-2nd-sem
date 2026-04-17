#include "addvoter.h"
#include "ui_addvoter.h"
#include "databasemanager.h"
#include "Voter.h"
#include <QSqlQuery>
#include <QSqlError>
#include "adminfunctionality.h"
void insertVoter(const Voter &v) {
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("INSERT INTO voters (cnin, name, username, password) "
                  "VALUES (:cnin, :name, :username, :password)");
    query.bindValue(":cnin", v.getCnin());
    query.bindValue(":name", v.getName());
    query.bindValue(":username", v.getUsername());
    query.bindValue(":password", v.getPassword());


        if (!query.exec()) {
            qDebug() << "Insert failed:" << query.lastError().text();
        }

}

addvoter::addvoter(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addvoter)
{

    ui->setupUi(this);


    if (!DatabaseManager::instance().connect()) {
        qDebug() << "Could not connect to DB";
        return;
    }


    model = new QSqlTableModel(this, DatabaseManager::instance().getDatabase());
    // model->setEditStrategy(QSqlTableModel :: OnFieldChange);
    model->setTable("voters");
    model->select();
    ui->tableView->setModel(model);
}

addvoter::~addvoter()
{
    delete ui;
}

void addvoter::on_pushButton_clicked()
{
    QString cnin = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    QString username = ui->lineEdit_3->text();
    QString password = ui->lineEdit_4->text();

    Voter voter(cnin, name, username, password);
    insertVoter(voter);
 model->select();
    // Optional: clear inputs
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}


void addvoter::on_pushButton_2_clicked()
{
    AdminFunctionality *af = new AdminFunctionality();
    af->show();
    this->close();
}

