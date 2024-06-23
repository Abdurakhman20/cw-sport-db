#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QSqlRelationalTableModel>
#include <QSqlDatabase>

class DataModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:

    explicit DataModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

    void initialize();
    bool addComplex(const QString &name, const QString &city, const QString &street, const QDate &constructionDate, int capacity, const QString &workingHours, const QString &website);
    bool removeComplex(int id);
    bool updateComplex(int id, const QString &name, const QString &city, const QString &street, const QDate &constructionDate, int capacity, const QString &workingHours, const QString &website);
    void fetchComplexes();

   private:

    QSqlDatabase db;
    int getAddressId(const QString &city, const QString &street);
    int getWebsiteId(const QString &website);
    bool addAddress(const QString &city, const QString &street);
    bool addWebsite(const QString &website);
};

#endif // DATAMODEL_H
