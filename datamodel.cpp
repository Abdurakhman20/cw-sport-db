#include "datamodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

DataModel::DataModel(QObject *parent, QSqlDatabase db): QSqlRelationalTableModel(parent, db), db(db)
{

}

void DataModel::initialize()
{
    setTable("complexes");
    setRelation(5, QSqlRelation("addresses", "id", "city"));
    setRelation(6, QSqlRelation("websites", "id", "url"));
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

bool DataModel::addComplex(const QString &name, const QString &city, const QString &street, const QDate &constructionDate, int capacity, const QString &workingHours, const QString &website)
{
    int addressId = getAddressId(city, street);
    int websiteId = getWebsiteId(website);

    if (addressId == -1) {
        if (!addAddress(city, street)) return false;
        addressId = getAddressId(city, street);
    }

    if (websiteId == -1) {
        if (!addWebsite(website)) return false;
        websiteId = getWebsiteId(website);
    }

    QSqlQuery query;
    query.prepare("INSERT INTO complexes (name, construction_date, capacity, working_hours, address_id, website_id) "
                  "VALUES (:name, :construction_date, :capacity, :working_hours, :address_id, :website_id)");
    query.bindValue(":name", name);
    query.bindValue(":construction_date", constructionDate);
    query.bindValue(":capacity", capacity);
    query.bindValue(":working_hours", workingHours);
    query.bindValue(":address_id", addressId);
    query.bindValue(":website_id", websiteId);

    if (!query.exec()) {
        qDebug() << "Error inserting complex:" << query.lastError().text();
        return false;
    }

    select();
    return true;
}

bool DataModel::removeComplex(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM complexes WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting complex:" << query.lastError().text();
        return false;
    }

    select();
    return true;
}

bool DataModel::updateComplex(int id, const QString &name, const QString &city, const QString &street, const QDate &constructionDate, int capacity, const QString &workingHours, const QString &website)
{
    int addressId = getAddressId(city, street);
    int websiteId = getWebsiteId(website);

    if (addressId == -1) {
        if (!addAddress(city, street)) return false;
        addressId = getAddressId(city, street);
    }

    if (websiteId == -1) {
        if (!addWebsite(website)) return false;
        websiteId = getWebsiteId(website);
    }

    QSqlQuery query;
    query.prepare("UPDATE complexes SET name = :name, construction_date = :construction_date, capacity = :capacity, working_hours = :working_hours, address_id = :address_id, website_id = :website_id "
                  "WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":construction_date", constructionDate);
    query.bindValue(":capacity", capacity);
    query.bindValue(":working_hours", workingHours);
    query.bindValue(":address_id", addressId);
    query.bindValue(":website_id", websiteId);

    if (!query.exec()) {
        qDebug() << "Error updating complex:" << query.lastError().text();
        return false;
    }

    select();
    return true;
}

void DataModel::fetchComplexes()
{
    select();
}

int DataModel::getAddressId(const QString &city, const QString &street)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM addresses WHERE city = :city AND street = :street");
    query.bindValue(":city", city);
    query.bindValue(":street", street);
    query.exec();

    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}

int DataModel::getWebsiteId(const QString &website)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM websites WHERE url = :url");
    query.bindValue(":url", website);
    query.exec();

    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}

bool DataModel::addAddress(const QString &city, const QString &street)
{
    QSqlQuery query;
    query.prepare("INSERT INTO addresses (city, street) VALUES (:city, :street)");
    query.bindValue(":city", city);
    query.bindValue(":street", street);

    if (!query.exec()) {
        qDebug() << "Error inserting address:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DataModel::addWebsite(const QString &website)
{
    QSqlQuery query;
    query.prepare("INSERT INTO websites (url) VALUES (:url)");
    query.bindValue(":url", website);

    if (!query.exec()) {
        qDebug() << "Error inserting website:" << query.lastError().text();
        return false;
    }

    return true;
}
