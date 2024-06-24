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
    QString mAddress;
    QString mWebsite;
    QString mComplexType;
    QString mComplexFinancing;
    int mComplexTypeID;
    int mComplexFinancingID;

public:
    //! Конструктор класса
    SportComplex();
    //! Значения конструктора класса
    SportComplex(
            const int mID,
            const QString mName,
            const QString mConstructionDate,
            const int mCapacity,
            const QString mWorkingHours,
            const QString mAddress,
            const QString mWebsite,
            const QString mComplexType,
            const QString mComplexFinancing,
            const int mComplexTypeID,
            const int mComplexFinancingID
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

    /// setter address
    void setAddress(const QString address);

    /// setter website
    void setWebsite(const QString website);

    /// setter complex type
    void setComplexType(const QString complexType);

    /// setter complex finansing
    void setComplexFinancing(const QString complexFinancing);

    /// setter complex type id
    void setComplexTypeID(const int complexTypeID);

    /// setter complex financing id
    void setComplexFinancingID(const int complexFinancingID);

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

    /// getter address
    QString getAddress() const;

    /// getter website
    QString getWebsite() const;

    /// getter complex type
    QString getComplexType() const;

    /// getter complex financing
    QString getComplexFinancing() const;

    /// getter complex type id
    int getComplexTypeID() const;

    /// getter complex financing id
    int getComplexFinancingID() const;

};
Q_DECLARE_METATYPE(SportComplex);

#endif // SPORTCOMPLEX_H
