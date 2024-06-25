#ifndef ADDITIONALTABLE_H
#define ADDITIONALTABLE_H

#include <QMainWindow>
#include <QSqlDatabase>

#include "additionaltableitem.h"
#include "additionaltablemodel.h"


namespace Ui {
class AdditionalTable;
}

class AdditionalTable : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase _db;
    QString mTableName;

public:
    explicit AdditionalTable(QWidget *parent, QSqlDatabase db, QString tableName);
    ~AdditionalTable();

private slots:
    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::AdditionalTable *ui;

    AdditionalTableModel *addtModel;
};

#endif // ADDITIONALTABLE_H
