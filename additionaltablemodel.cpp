#include "additionaltablemodel.h"

AdditionalTableModel::AdditionalTableModel(QObject *parent, QSqlDatabase db, QString tableName)
    : QAbstractTableModel {parent}
    , _db(db)
    , mTableName(tableName)
{}

QSqlError AdditionalTableModel::initLoad()
{
    QSqlQuery query(_db);
    QString selectData = "SELECT * FROM " + mTableName;

    if (!query.exec(selectData)) {
        return query.lastError();
    }

    while (query.next()) {
        AdditionalTableItem *item = new AdditionalTableItem(query.value(0).toInt(),
                                          query.value(1).toString());

        this->items.push_back(*item);
    }

    return query.lastError();
}

int AdditionalTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : items.size();
}

int AdditionalTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : columnsCount;
}

QVariant AdditionalTableModel::data(const QModelIndex &index, int role) const
{
    if (!checkIndex(index, CheckIndexOption::IndexIsValid))
        return QVariant();

    int row = index.row();
    int col = index.column();

    switch(role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch (col) {
        case 0:
            return items[row].getID();
        case 1:
            return items[row].getName();
        }

        break;
    default:
        return QVariant();
    }

    return QVariant();

}

QVariant AdditionalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section) {
        case 0:
            return QString("ID");
        case 1:
            return QString(tr("Name"));
        }
    }

    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        return QString::number(section + 1);

    return QVariant();
}

Qt::ItemFlags AdditionalTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid() && index.column() != 0)
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable |defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

bool AdditionalTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!checkIndex(index, CheckIndexOption::IndexIsValid))
        return false;

    int col = index.column();

    QSqlQuery query(_db);
    QString updateItemQuery = "UPDATE " + mTableName + " SET name = :name WHERE id = :itemID";

    query.prepare(updateItemQuery);
    query.bindValue(":name", value.toString());
    query.bindValue(":itemID", items[index.row()].getID());

    if (!query.exec()) {
        QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
        QMessageBox::critical(pMainWindow,
                              tr("Error update item!"), query.lastError().text());
        return 0;
    }


    if (role == Qt::EditRole) {
        switch (col) {
        case 1:
            items[index.row()].setName(value.toString()); break;
        }

        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    return false;

}

bool AdditionalTableModel::insertRow(int position, AdditionalTableItem &value)
{
    beginInsertRows(QModelIndex(), position, position);

    QSqlQuery query(_db);

    if (!query.exec("INSERT INTO " + mTableName + "(name) VALUES ('')" +
                    " RETURNING id")) {
        QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
        QMessageBox::critical(pMainWindow,
                              tr("Error select!"), query.lastError().text());
        return false;
    }

    if (query.next())
        value.setID(query.value(0).toInt());

    items.push_back(value);

    endInsertRows();

    return true;
}

bool AdditionalTableModel::removeRow(const int position)
{
    if (items.isEmpty()) {
        return false;
    }

    beginRemoveRows(QModelIndex(), position, position);

    QSqlQuery query(_db);

    if (!query.exec("DELETE FROM " + mTableName +
                    " WHERE id = " + QString::number(items[position].getID()))) {

        QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
        QMessageBox::critical(pMainWindow,
                              tr("Error select!"), query.lastError().text());
        return false;
    }

    items.removeAt(position);

    endRemoveRows();

    return true;
}
