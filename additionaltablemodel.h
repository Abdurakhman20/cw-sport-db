#ifndef ADDITIONALTABLEMODEL_H
#define ADDITIONALTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QDebug>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <additionaltableitem.h>

class AdditionalTableModel: public QAbstractTableModel
{
    /// Список объектов  класса, который описывает одну стрчоку в файле данных
    QList<AdditionalTableItem> items;
    QSqlDatabase _db;
    QString mTableName;

    int rows;
    int columnsCount = 2;
public:
    AdditionalTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase(), QString tableName = "");

    long long count() const;
    void setTableName(const QString &newTableName);
    QSqlError initLoad();

public:
    /// Возвращает количество строк в таблице
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Возвращает количество колонн в таблице
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Возвраащает данные при отображении ячейки таблицы
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Возвращает данные для отображения в заголовке таблицы.
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /// Задаёт правила работы ячейки таблицы.
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /// Вставляет данные из делегата в контейнер при редактировании ячейки
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /// Вставляет строчку в таблицу на основе нового объекта класса Supplier и возвращает
    bool insertRow(int position, AdditionalTableItem &value);

    /// Удаляет строчку из таблице по переданному индексу
    bool removeRow(const int position);
};

#endif // ADDITIONALTABLEMODEL_H
