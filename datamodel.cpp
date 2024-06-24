#include "datamodel.h"

DataModel::DataModel(QObject *parent, QSqlDatabase db)
    : QAbstractTableModel{parent}
    , _db(db)
    , rows(20)
{}

QSqlError DataModel::initLoad()
{
    QSqlQuery query(_db);
    QString selectRows = QString(
                                "SELECT c.id, c.name, c.construction_date, c.capacity, c.working_hours, c.address, c.website, ct.type, cf.financing, c.complex_type_id, c.complex_financing_id "
                                "FROM %1 c LEFT JOIN complex_types ct ON c.complex_type_id = ct.id "
                                "LEFT JOIN complex_financing cf ON c.complex_financing_id = cf.id "
                                "ORDER BY c.id DESC FETCH FIRST 20 ROWS ONLY"
    ).arg(mTableName);

    if (!query.exec(selectRows)) {
        return query.lastError();
    }

    while (query.next()) {
        SportComplex *sportComplex = new SportComplex(
                                            query.value(0).toInt(),
                                            query.value(1).toString(),
                                            query.value(2).toString(),
                                            query.value(3).toInt(),
                                            query.value(4).toString(),
                                            query.value(5).toString(),
                                            query.value(6).toString(),
                                            query.value(7).toString(),
                                            query.value(8).toString(),
                                            query.value(9).toInt(),
                                            query.value(10).toInt());

        this->sportComplexes.push_back(*sportComplex);
    }

    return query.lastError();

}

/// Метод извлекает из БД фактическое количество строк
long long DataModel::count() const
{
    QSqlQuery query(_db);
    QString selectRowsCount = "SELECT COUNT(*) FROM " + mTableName;

    if (!query.exec(selectRowsCount)) {

        QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
        QMessageBox::critical(pMainWindow,
                              tr("Error select!"), query.lastError().text());
        return 0;
    }

    /// Узнаем сколько строк всего в БД
    if (query.next())
        return query.value(0).toLongLong();
    else
        return 0;
}


const QString &DataModel::tableName() const
{
    return mTableName;
}

void DataModel::setTableName(const QString &newTableName)
{
    mTableName = newTableName;
}


int DataModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : rows;
}

int DataModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 9;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
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
            return sportComplexes[row].getID();
        case 1:
            return sportComplexes[row].getName();
        case 2:
            return sportComplexes[row].getConstructionDate();
        case 3:
            return sportComplexes[row].getCapacity();
        case 4:
            return sportComplexes[row].getWorkingHours();
        case 5:
            return sportComplexes[row].getAddress();
        case 6:
            return sportComplexes[row].getWebsite();
        case 7:
            return sportComplexes[row].getComplexType();
        case 8:
            return sportComplexes[row].getComplexFinancing();
        }

        break;
    default:
        return QVariant();
    }

    return QVariant();

}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section) {
        case 0:
            return QString("ID");
        case 1:
            return QString(tr("Name"));
        case 2:
            return QString(tr("Construction Date"));
        case 3:
            return QString(tr("Capacity"));
        case 4:
            return QString(tr("Working Hours"));
        case 5:
            return QString(tr("Address"));
        case 6:
            return QString(tr("Website"));
        case 7:
            return QString(tr("Complex Type"));
        case 8:
            return QString(tr("Complex Financing"));
        }
    }

    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        return QString::number(section + 1);

    return QVariant();

}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid() && index.column() != 0)
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable |defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;

}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!checkIndex(index, CheckIndexOption::IndexIsValid))
        return false;

    if (value.toString() == "")
        return true;

    int col = index.column();

    int newComplexTypeID = NULL;
    int newComplexFinancingID = NULL;

    if(!_db.transaction()) {
        qDebug() << "Transaction failed!";
        return false;
    }

    if (col == 7) {
        QSqlQuery query(_db);

        query.prepare("SELECT id FROM complex_types WHERE type = :type");
        query.bindValue(":type", value.toString());

        if (!query.exec()) {
            QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
            QMessageBox::critical(pMainWindow,
                                  tr("Error select!"), query.lastError().text());
            _db.rollback();
            return 0;
        }

        if (query.next()) {
            newComplexTypeID = query.value(0).toInt();
        } else {
            QSqlQuery query(_db);

            query.prepare("INSERT INTO complex_types(type) VALUES (:complex_type_id) RETURNING id");
            query.bindValue(":complex_type_id", value.toString());

            if (!query.exec()) {
                QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
                QMessageBox::critical(pMainWindow,
                                      tr("Error insert complex_type_id!"), query.lastError().text());
                _db.rollback();
                return 0;
            }

            if (query.next()) {
                newComplexTypeID = query.value(0).toInt();
                qDebug() << query.value(0).toInt();
            }
        }

        sportComplexes[index.row()].setComplexTypeID(newComplexTypeID);
    }

    if (col == 8) {
        QSqlQuery query(_db);

        query.prepare("SELECT id  FROM complex_financing WHERE financing = :financing");
        query.bindValue(":financing", value.toString());

        if (!query.exec()) {
            QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
            QMessageBox::critical(pMainWindow,
                                  tr("Error select!"), query.lastError().text());
            _db.rollback();
            return false;
        }

        if (query.next()) {
            newComplexFinancingID = query.value(0).toInt();
        } else {
            QSqlQuery query(_db);

            query.prepare("INSERT INTO complex_financing(financing) VALUES (:complex_financing_id) RETURNING id");
            query.bindValue(":complex_financing_id", value.toString());

            if (!query.exec()) {
                QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
                QMessageBox::critical(pMainWindow,
                                      tr("Error insert complex_financing_id!"), query.lastError().text());
                _db.rollback();
                return 0;
            }

            if (query.next()) {
                newComplexFinancingID = query.value(0).toInt();
                qDebug() << query.value(0).toInt();
            }
        }

        sportComplexes[index.row()].setComplexFinancingID(newComplexFinancingID);
    }

    if (role == Qt::EditRole) {
        switch (col) {
        case 1:
            sportComplexes[index.row()].setName(value.toString()); break;
        case 2:
            sportComplexes[index.row()].setConstructionDate(value.toString()); break;
        case 3:
            sportComplexes[index.row()].setCapacity(value.toInt()); break;
        case 4:
            sportComplexes[index.row()].setWorkingHours(value.toString()); break;
        case 5:
            sportComplexes[index.row()].setAddress(value.toString()); break;
        case 6:
            sportComplexes[index.row()].setWebsite(value.toString()); break;
        case 7:
            sportComplexes[index.row()].setComplexType(value.toString()); break;
        case 8:
            sportComplexes[index.row()].setComplexFinancing(value.toString()); break;
        }

        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    }

    QSqlQuery query(_db);
    QString updateSportComplexes = "UPDATE " + mTableName + " SET name = :name, construction_date = :cd, capacity = :capacity,"
                                + " working_hours = :wh, address = :address, website = :website, complex_type_id = :ct_id,"
                                + " complex_financing_id = :cf_id WHERE id = :complexID";

    query.prepare(updateSportComplexes);
    query.bindValue(":name", sportComplexes[index.row()].getName());
    query.bindValue(":cd", sportComplexes[index.row()].getConstructionDate());
    query.bindValue(":capacity", sportComplexes[index.row()].getCapacity());
    query.bindValue(":wh", sportComplexes[index.row()].getWorkingHours());
    query.bindValue(":address", sportComplexes[index.row()].getAddress());
    query.bindValue(":website", sportComplexes[index.row()].getWebsite());
    query.bindValue(":ct_id", sportComplexes[index.row()].getComplexTypeID());
    query.bindValue(":cf_id", sportComplexes[index.row()].getComplexFinancingID());
    query.bindValue(":complexID", sportComplexes[index.row()].getID());

    if (!query.exec()) {
        QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
        QMessageBox::critical(pMainWindow,
                              tr("Error update sport complexes!"), query.lastError().text());
        _db.rollback();
        return 0;
    }

    if (!_db.commit()) {
        _db.rollback();
        qDebug() << _db.lastError().text();
        return false;
    }


    return true;
}


bool DataModel::insertRow(int position, SportComplex &value) {
    beginInsertRows(QModelIndex(), position, position);

    QSqlQuery query(_db);

    if (!query.exec("INSERT INTO " + mTableName + " DEFAULT VALUES" +
                    " RETURNING id")) {
        QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
        QMessageBox::critical(pMainWindow,
                              tr("Error select!"), query.lastError().text());
        return false;
    }

    if (query.next())
        value.setID(query.value(0).toInt());

    sportComplexes.push_front(value);

    endInsertRows();

    return true;
}

bool DataModel::removeRow(const int position) {
    if (sportComplexes.isEmpty()) {
        return false;
    }

    beginRemoveRows(QModelIndex(), position, position);

    QSqlQuery query(_db);

    if (!query.exec("DELETE FROM " + mTableName +
                    " WHERE id = " + QString::number(sportComplexes[position].getID()))) {

        QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
        QMessageBox::critical(pMainWindow,
                              tr("Error select!"), query.lastError().text());
        return false;
    }

    sportComplexes.removeAt(position);

    endRemoveRows();

    return true;
}

void DataModel::fetchMore(const QModelIndex &pos)
{
    if (pos.isValid())
        return;

    QSqlQuery query(_db);
    // Делаем запрос новых 20 строк со смещением в 20 имеющихся строк
    QString selectRows = QString(
        "SELECT c.id, c.name, c.construction_date, c.capacity, c.working_hours, c.address, c.website, ct.type, cf.financing, c.complex_type_id, c.complex_financing_id "
        "FROM %1 c LEFT JOIN complex_types ct ON c.complex_type_id = ct.id "
        "LEFT JOIN complex_financing cf ON c.complex_financing_id = cf.id "
        "ORDER BY c.id DESC OFFSET %2 ROWS FETCH FIRST 20 ROWS ONLY"
    ).arg(mTableName).arg(rows);

    if (!query.exec(selectRows)) {
        QWidget *pMainWindow = qobject_cast<QWidget *>(this->parent());
        QMessageBox::critical(pMainWindow,
                              tr("Error select!"), query.lastError().text());
        return;
    }

    // Загружаем новую порцию в 20 строк в объект "students"
    while (query.next()) {
        SportComplex *sportComplex = new SportComplex(
                                            query.value(0).toInt(),
                                            query.value(1).toString(),
                                            query.value(2).toString(),
                                            query.value(3).toInt(),
                                            query.value(4).toString(),
                                            query.value(5).toString(),
                                            query.value(6).toString(),
                                            query.value(7).toString(),
                                            query.value(8).toString(),
                                            query.value(9).toInt(),
                                            query.value(10).toInt());

        this->sportComplexes.push_back(*sportComplex);
    }

    // Берём текущее количество строк, как начало отсчёта
    const int start = rows;

    // Определяем, сколько ещё осталось строк загрузить
    const int remainder = sportComplexes.count() - start;
    // Определяем, возможно ли ещё загрузить 20 строк или их осталось меньше 20
    const int itemsToFetch = qMin(20, remainder);

    // Если строк меньше 0, то выходим, так как больше нет строк для загрузки
    if (itemsToFetch <= 0)
        return;

    // Начинаем вставлять строки в модель.
    // Например, вставляются строки с 20 до 39
    beginInsertRows(QModelIndex(), start, start + itemsToFetch - 1);

    // Добавляем к уже имеющимся строкам ещё
    rows += itemsToFetch;

    // Заканчиваем вставку
    endInsertRows();
}

bool DataModel::canFetchMore(const QModelIndex &parent) const
{
    if (parent.isValid())
        return false;

    return (rows < count());
}




