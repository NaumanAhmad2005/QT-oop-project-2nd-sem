#include "avalableelections.h"
#include "ui_avalableelections.h"
#include <databasemanager.h>
#include "voterfunctionality.h"
avalableelections::avalableelections(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::avalableelections)
{
    ui->setupUi(this);
    if (!DatabaseManager::instance().connect()) {
        qDebug() << "Could not connect to DB";
        return;
    }
    model = new QSqlTableModel(this,  DatabaseManager::instance().getDatabase());
    model->setTable("electionsss");
    model->select();
    ui->tableView->setModel(model);
}

avalableelections::~avalableelections()
{
    delete ui;
}

void avalableelections::on_pushButton_clicked()
{
    voterfunctionality *VF = new voterfunctionality("0");
    VF->show();
    this->close();
}

