#include "castvote.h"
#include "ui_castvote.h"
#include "databasemanager.h"
#include "QSqlQuery"
#include "QString"
#include "QMessageBox"
#include "QSqlError"
#include "voterfunctionality.h"
#include "UserManager.h"
castVote::castVote(const QString &voterId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::castVote)
    , m_voterId(voterId)
{
    ui->setupUi(this);
    if (!DatabaseManager::instance().connect()) {
        qDebug() << "Could not connect to DB";
        return;
    }
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

castVote::~castVote()
{
    delete ui;
}

void castVote::on_comboBox_currentTextChanged(const QString &text)
{
    ui->comboBox_2->clear();

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT id FROM candidates WHERE electionId = :eid");
    query.bindValue(":eid", text);
    query.exec();

    while (query.next()) {
        QString candidateId = query.value(0).toString();
        ui->comboBox_2->addItem(candidateId);
    }
}


void castVote::on_pushButton_clicked()
{
    QString electionId = ui->comboBox->currentText();
    QString candidateId = ui->comboBox_2->currentText();
    QString voterId = m_voterId;

    QSqlDatabase db = DatabaseManager::instance().getDatabase();

    // Step 1: Check if already voted
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT * FROM votes WHERE voter_id = :voter AND election_id = :election");
    checkQuery.bindValue(":voter", voterId);
    checkQuery.bindValue(":election", electionId);

    if (checkQuery.next()) {
        QMessageBox::warning(this, "Already Voted", "You have already voted in this election.");
        return;
    }

    // Step 2: Insert vote
    QSqlQuery insertQuery(db);
    insertQuery.prepare("INSERT INTO votes (voter_id, election_id, candidate_id) "
                        "VALUES (:voter, :election, :candidate)");
    insertQuery.bindValue(":voter", voterId);
    insertQuery.bindValue(":election", electionId);
    insertQuery.bindValue(":candidate", candidateId);

    if (!insertQuery.exec()) {
        qDebug() << insertQuery.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to record your vote.");
        return;
    }

    // Step 3: Increment candidate vote count
    QSqlQuery updateQuery(db);
    updateQuery.prepare("UPDATE candidates SET vote = vote + 1 WHERE id = :cid");
    updateQuery.bindValue(":cid", candidateId);

    if (!updateQuery.exec()) {
        QMessageBox::warning(this, "Warning", "Vote recorded, but candidate count update failed.");
        return;
    }

    // ✅ Refresh model AFTER vote count is updated
    model->select();

    // ✅ Final confirmation
    QMessageBox::information(this, "Vote Cast", "Your vote has been successfully cast!");
    ui->pushButton->setEnabled(false);

}


void castVote::on_pushButton_2_clicked()
{
    voterfunctionality *Vdash = new voterfunctionality(m_voterId);
    Vdash->show();
    this->close();
}

