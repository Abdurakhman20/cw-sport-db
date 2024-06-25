#include "additionaltable.h"
#include "ui_additionaltable.h"

AdditionalTable::AdditionalTable(QWidget *parent, QSqlDatabase db, QString tableName) :
    QMainWindow(parent)
    , ui(new Ui::AdditionalTable)
    , _db(db)
    , mTableName(tableName)
    , addtModel(new AdditionalTableModel(this, db, tableName))
{
    ui->setupUi(this);

    addtModel->initLoad();
    ui->tableView->setModel(addtModel);
    ui->tableView->verticalHeader()->setVisible(false);

    ui->tableView->setAttribute(Qt::WA_DeleteOnClose);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    this->setWindowTitle(tableName);
}

AdditionalTable::~AdditionalTable()
{
    delete ui;
}

void AdditionalTable::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu=new QMenu(ui->tableView);

    QModelIndex index=ui->tableView->indexAt(pos);

    QAction *deleteAction = new QAction(tr("Delete row"), ui->tableView);
    QAction *addAction = new QAction(tr("Add row"), ui->tableView);

    menu->addAction(deleteAction);
    menu->addAction(addAction);

    QAction *selectedItem = menu->exec(ui->tableView->viewport()->mapToGlobal(pos));

    if (selectedItem == deleteAction && index.isValid()) {
        QMessageBox::StandardButton resBtn =
            QMessageBox::question(this, tr("Delete row"), tr("Are you sure you want to delete the line?\n"),
                                  QMessageBox::No | QMessageBox::Yes);

        if (resBtn == QMessageBox::Yes)
            addtModel->removeRow(index.row());
        else
            return;

    } else if (selectedItem == addAction) {
        AdditionalTableItem newItem;

        auto placeholder = this;
        if (placeholder == nullptr)
            return;

        addtModel->insertRow(addtModel->rowCount(), newItem);
    }
}

