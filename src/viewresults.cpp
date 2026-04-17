#include "viewresults.h"
#include "ui_viewresults.h"
#include <databasemanager.h>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>
#include <QLayout>
#include <adminfunctionality.h>
#include <QRandomGenerator>

// #include <ctime>
// QT_CHARTS_USE_NAMESPACE
viewResults::viewResults(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::viewResults)
{
    // qsrand(static_cast<uint>(time(nullptr)));
    ui->setupUi(this);
    if (!DatabaseManager::instance().connect()) {
        QMessageBox::critical(this, "Error", "Database not open.");
        return;
    }

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.exec("SELECT id FROM electionsss");

    while (query.next()) {
        QString eid = query.value(0).toString();
        ui->comboBox->addItem(eid);
    }

}

viewResults::~viewResults()
{
    delete ui;
}

void viewResults::on_comboBox_currentTextChanged(const QString &electionId)
{
    QPieSeries *series = new QPieSeries();

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT name, vote FROM candidates WHERE electionId = :eid");
    query.bindValue(":eid", electionId);
    query.exec();
    qDebug() << "Candidates for election ID:" << electionId;

    while (query.next()) {
        QString name = query.value(0).toString();
        int votes = query.value(1).toInt();
        qDebug() << "Candidate:" << name << "| Votes:" << votes;
        series->append(name, votes);
    }
    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible(true);                      // show label always
        slice->setPen(QPen(Qt::black, 2));                 // border styling
        slice->setBrush(QColor::fromHsv(QRandomGenerator::global()->bounded(360), 255, 200));
    }
    if (!series->slices().isEmpty()) {
        series->slices().at(0)->setExploded(true);
        series->slices().at(0)->setLabelVisible(true);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Election Result Pie Chart");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QLayout *oldLayout = ui->chartContainer->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // ✅ Add new chart layout
    QVBoxLayout *chartLayout = new QVBoxLayout(ui->chartContainer);
    chartLayout->addWidget(chartView);
}



void viewResults::on_pushButton_2_clicked()
{
    AdminFunctionality *AF = new AdminFunctionality();
    AF->show();
    this->close();
}

