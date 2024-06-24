#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connectwindow.h"

#include <QMainWindow>

#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionConnect_triggered();
    void handleConnectionDetails(const QString &host, const int &port, const QString &database, const QString &user, const QString &password);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
