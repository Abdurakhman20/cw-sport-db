#include "mainwindow.h"
#include "ui_mainwindow.h"

// for debug
#include <QDebug>
#include <QMessageBox>

// for sql
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>

// basic
#include <QString>

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
    ConnectWindow *connectWindow = new ConnectWindow(this);

    connect(connectWindow, &ConnectWindow::connectionDetailsEntered, this, &MainWindow::handleConnectionDetails);
    connect(connectWindow, &ConnectWindow::destroyed, connectWindow, &QObject::deleteLater);
    connectWindow->show();

}

void MainWindow::handleConnectionDetails(const QString &host, const QString &database, const QString &user, const QString &password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setDatabaseName(database);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        QMessageBox::critical(this, "Connection Failed", db.lastError().text());
    } else {
        QMessageBox::information(this, "Connection Successful", "Connected to the database successfully!");
    }

}



