#include "connectwindow.h"
#include "ui_connectwindow.h"

#include <QString>

ConnectWindow::ConnectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void ConnectWindow::on_connectPushButton_clicked()
{
    QString host = ui->hostLineEdit->text();
    int port = ui->portLineEdit->text().toInt();
    QString database = ui->databaseLineEdit->text();
    QString user = ui->userLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    emit connectionDetailsEntered(host, port, database, user, password);

    close();

}


void ConnectWindow::on_cancelPushButton_clicked()
{
    close();
}

