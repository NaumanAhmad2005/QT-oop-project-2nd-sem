#include "createcandidatedamn.h"
#include "ui_createcandidatedamn.h"
#include "candidate.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "adminfunctionality.h"
void insertCandidate(const Candidate &c) {
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("INSERT INTO candidates (name, partyAffiliation, electionId) "
                  "VALUES (:name, :partyAffiliation, :electionId)");
    query.bindValue(":name", c.getName());
    query.bindValue(":partyAffiliation", c.getParty());
    query.bindValue(":electionId", c.getElectionId());

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError();
    }
}

CreateCandidatedamn::CreateCandidatedamn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateCandidatedamn)
{
    ui->setupUi(this);
    //  Connect to the DB
    if (!DatabaseManager::instance().connect()) {
        qDebug() << "Could not connect to DB";
        return;
    }
    //  push all elections IDs in the combo box
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.exec("SELECT id FROM electionsss");
    while (query.next()) {
        QString electionId = query.value(0).toString();
        ui->comboBox->addItem(electionId);
    }
    //  Set up the table model
    model = new QSqlTableModel(this, DatabaseManager::instance().getDatabase());
    model->setTable("candidates");
    model->select();
    ui->tableView->setModel(model);
}
CreateCandidatedamn::~CreateCandidatedamn()
{
    delete ui;
}
void CreateCandidatedamn::on_pushButton_clicked()
{
    // QString id = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    int aff = ui->lineEdit_3->text().toInt();
    QString electionId = ui->comboBox->currentText();
    Candidate c("", name, aff, electionId);
    insertCandidate(c);
    model->select();
    // ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

void CreateCandidatedamn::on_pushButton_2_clicked()
{
    AdminFunctionality *DD =new AdminFunctionality();
    DD->show();
    this->close();
}

