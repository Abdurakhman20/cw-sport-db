#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QWidget>

#include "sportcomplex.h"

class DataModel : public QAbstractTableModel
{
    Q_OBJECT

    /// Контейнер для хранения данных
    QList<SportComplex> sportComplexes;
    QSqlDatabase _db;
    QString mTableName;

    int rows;

public:
    /// Конструктор класса
    explicit DataModel(QObject *parent = nullptr,
                             QSqlDatabase db = QSqlDatabase());

    QSqlError initLoad();

    long long count() const;

    const QString &tableName() const;

    void setTableName(const QString &newTableName);

public:
    /// Возвращает количество строк в таблице
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Возвращает количетсво колонн в табилце
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Возвраащает данные при отображении ячейки таблицы
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Возвращает данные для отображения в заголовке таблицы.
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /// Задаёт правила работы ячейки таблицы.
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /// Вставляет данные из делегата в контейнер при редактировании ячейки
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /// Вставляет строчку в таблицу на основе нового объекта класса SportComplex и возвращает
    bool insertRow(int position, SportComplex &value);

    /// Удаляет строчку из таблице по переданному индексу
    bool removeRow(const int position);

    /// Метод загружает новую порцию данных
    void fetchMore(const QModelIndex &parent) override;

    /// Метод узнаёт, можно ли загрузить ещё порцию данных
    bool canFetchMore(const QModelIndex &parent) const override;
};

#endif // DATAMODEL_H
