#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connectwindow.h"

#include <QMainWindow>
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QSettings>
#include <QString>
#include <QMenu>
#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDir>
#include <QDropEvent>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <datamodel.h>
#include <datadelegate.h>
#include <additionaltable.h>
#include <connectwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /// Метод получения настрое приложения
    void getSettings();

    /// Метод установки настроек приложения
    void setSettings();

    /// Создаёт меню для выбора языка
    void createLanguageMenu();

    /// Меняет текущий язык на выбранный в меню
    void switchLanguage(QAction *action);

    QModelIndex tableFind(const QString&);

    void resetFind();

private slots:
    void on_actionConnect_triggered();

    void handleConnectionDetails(const QString &host, const int &port, const QString &database, const QString &user, const QString &password);

    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_actionComplex_Types_triggered();

    void on_actionComplex_Financing_triggered();

    void on_actionAbout_the_developer_triggered();

private:
    Ui::MainWindow *ui;

    QString connectionName;
    QSqlDatabase db;
    int selectedColumn;

    DataModel *dModel;
    QSortFilterProxyModel *proxyModel;

    QTranslator appTranslator;
    QTranslator qtTranslator;
    QActionGroup *languageActionGroup;
    QString qmPath;
};
#endif // MAINWINDOW_H
