#ifndef SPORTCOMPLEX_H
#define SPORTCOMPLEX_H

#include <QString>
#include <QVariant>

//! \brief Класс для описания спортивного комплекса
class SportComplex
{
private:
    int mID;
    QString mName;
    QString mConstructionDate;
    int mCapacity;
    QString mWorkingHours;
    int mAddressID;
    int mWebsiteID;

public:
    //! Конструктор класса
    SportComplex();
    //! Значения конструктора класса
    SportComplex(
            const int id,
            const QString name,
            const QString constructionDate,
            const int capacity,
            const QString workingHours,
            const int addressID,
            const int websiteID
    );

    /// Устанавливаем Функции setters

    /// setter id
    void setID(const int id);

    /// setter name
    void setName(const QString name);

    /// setter construction date
    void setConstructionDate(const QString constructionDate);

    /// setter capacity
    void setCapacity(const int capacity);

    /// setter working hours
    void setWorkingHours(const QString workingHours);

    /// setter address id
    void setAddressID(const int addressID);

    /// setter website id
    void setWebsiteID(const int websiteID);

    /// Устанавливаем функции getters

    /// getter id
    int getID() const;

    ///getter name
    QString getName() const;

    /// getter construction date
    QString getConstructionDate() const;

    /// getter capacity
    int getCapacity() const;

    /// getter working hours
    QString getWorkingHours() const;

    /// getter address id
    int getAddressID() const;

    /// getter website id
    int getWebsiteID() const;

};
Q_DECLARE_METATYPE(SportComplex);

#endif // SPORTCOMPLEX_H
