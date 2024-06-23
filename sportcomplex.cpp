#include "sportcomplex.h"

SportComplex::SportComplex()
{
    mID = 0;
    mName = "";
    mConstructionDate = "";
    mCapacity = 0;
    mWorkingHours = "";
    mAddressID = 0;
    mWebsiteID = 0;
}

SportComplex::SportComplex(
        const int id,
        const QString name,
        const QString constructionDate,
        const int capacity,
        const QString workingHours,
        const int addressID,
        const int websiteID
        )
{
    mID = id;
    mName = name;
    mConstructionDate = constructionDate;
    mCapacity = capacity;
    mWorkingHours = workingHours;
    mAddressID = addressID;
    mWebsiteID = websiteID;
}

/// Реализуем Функции setters

/// setter id
void SportComplex::setID(const int id) {
    mID = id;
}

/// setter name
void SportComplex::setName(const QString name) {
    mName = name;
}

/// setter construction date
void SportComplex::setConstructionDate(const QString constructionDate) {
    mConstructionDate = constructionDate;
}

/// setter capacity
void SportComplex::setCapacity(const int capacity) {
    mCapacity = capacity;
}

/// setter working hours
void SportComplex::setWorkingHours(const QString workingHours) {
    mWorkingHours = workingHours;
}

/// setter address id
void SportComplex::setAddressID(const int addressID) {
    mAddressID = addressID;
}

/// setter website id
void SportComplex::setWebsiteID(const int websiteID) {
    mWebsiteID = websiteID;
}


/// Реализуем Функции getters


/// getter id
int SportComplex::getID() const {
    return mID;
}

///getter name
QString SportComplex::getName() const {
    return mName;
}

/// getter construction date
QString SportComplex::getConstructionDate() const {
    return mConstructionDate;
}

/// getter capacity
int SportComplex::getCapacity() const {
    return mCapacity;
}

/// getter working hours
QString SportComplex::getWorkingHours() const {
    return mWorkingHours;
}

/// getter address id
int SportComplex::getAddressID() const {
    return mAddressID;
}

/// getter website id
int SportComplex::getWebsiteID() const {
    return mWebsiteID;
}






