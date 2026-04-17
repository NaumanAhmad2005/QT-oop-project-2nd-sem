#include "createelction.h"
#include "ui_createelction.h"
#include "electiondamn.h"
#include "adminfunctionality.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "QVariant"
#include "databasemanager.h"


const QString CONNECTION_NAME = "main_connection";

bool connectToDatabase() {
    if (QSqlDatabase::contains(CONNECTION_NAME)) {
        qDebug() << "Database already connected.";
        return true;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
    db.setDatabaseName("project.db");

    if (!db.open()) {
        qDebug() << "Error: connection failed!" << db.lastError();
        return false;
    }

    QSqlQuery query(db);

    query.exec("CREATE TABLE IF NOT EXISTS electionsss ("
               "id TEXT PRIMARY KEY , "
               "name TEXT, "
               "type TEXT, "
               "district TEXT, "
               "country TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS candidates ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, "
               "partyAffiliation INTEGER, "
               "vote INTEGER DEFAULT 0, "
               "electionId TEXT, "
               "FOREIGN KEY(electionId) REFERENCES electionsss(id))");

    query.exec("CREATE TABLE IF NOT EXISTS voters ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "cnin TEXT, "
               "name TEXT, "
               "username TEXT UNIQUE, "
               "password TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS votes ("
               "voter_id TEXT, "
               "election_id TEXT, "
               "candidate_id TEXT, "  // ✅ fixed typo: was 'candidate_is'
               "PRIMARY KEY (voter_id, election_id), "
               "FOREIGN KEY (voter_id) REFERENCES voters(id), "
               "FOREIGN KEY (election_id) REFERENCES electionsss(id), "
               "FOREIGN KEY (candidate_id) REFERENCES candidates(id))");

    return true;
}

void insertElection(const Election &election) {
    QSqlDatabase db = QSqlDatabase::database(CONNECTION_NAME);
    QSqlQuery query(db);

    query.prepare("INSERT INTO electionsss (id, name, type, district, country) "
                  "VALUES (:id, :name, :type, :district, :country)");

    query.bindValue(":id", election.getElectionId());
    query.bindValue(":name", election.getElectionName());
    query.bindValue(":type", election.getElectionType());

    if (const LocalElection* local = dynamic_cast<const LocalElection*>(&election)) {
        query.bindValue(":district", local->getDistrict());
        query.bindValue(":country", QVariant());
    } else if (const NationalElection* national = dynamic_cast<const NationalElection*>(&election)) {
        query.bindValue(":district", QVariant());
        query.bindValue(":country", national->getCountry());
    } else {
        query.bindValue(":district", QVariant());
        query.bindValue(":country", QVariant());
    }

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
    }
}

createElction::createElction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createElction)
{
    ui->setupUi(this);
    connectToDatabase();

    model = new QSqlTableModel(this, QSqlDatabase::database(CONNECTION_NAME));
    model->setTable("electionsss");
    model->select();
    ui->tableView->setModel(model);
}

createElction::~createElction()
{
    delete ui;
}

void createElction::on_pushButton_clicked()
{
    Election *kuchbhi = nullptr;
    QString id = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    QString type = ui->lineEdit_3->text();
    QString region = ui->lineEdit_4->text();

    if (type == "local") {
        kuchbhi = new LocalElection(id, name, region);
    } else {
        kuchbhi = new NationalElection(id, name, region);
    }

    insertElection(*kuchbhi);

    model->select();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();

    delete kuchbhi;  // Don't forget to clean memory
}

void createElction::on_pushButton_2_clicked()
{
    AdminFunctionality *af = new AdminFunctionality();
    this->close();
    af->show();
}
