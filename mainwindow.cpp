#include "mainwindow.h"
#include "ui_mainwindow.h"

// Basic
#include <QDebug>
#include <QMessageBox>

// DataBase
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (QSqlDatabase::isDriverAvailable("QPSQL")) {

        qDebug() << "SUCCESS: PostgreSQL driver was found!";
    }
    else {

        qDebug() << "FAILED: PostgreSQL driver was not found!";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionConnect_triggered()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("cw_sport_db");
    db.setPassword("sql20230221");
    db.setUserName("postgres");

    if(!db.open()) {

        QMessageBox::warning(this, tr("Application"), db.lastError().text());
        qDebug() << db.connectOptions();
        return;
    } else {

        qDebug() << "SUCCESS: The connection was successful!";
    }
}

