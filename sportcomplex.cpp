#include "sportcomplex.h"

SportComplex::SportComplex()
{
    mID = 0;
    mName = "";
    mConstructionDate = "";
    mCapacity = 0;
    mWorkingHours = "";
    mAddress = "";
    mWebsite = "";
    mComplexType = "";
    mComplexFinancing = "";
}

SportComplex::SportComplex(
        const int id,
        const QString name,
        const QString constructionDate,
        const int capacity,
        const QString workingHours,
        const QString address,
        const QString website,
        const QString complexType,
        const QString complexFinancing,
        const int complexTypeID,
        const int complexFinancingID
        )
{
    mID = id;
    mName = name;
    mConstructionDate = constructionDate;
    mCapacity = capacity;
    mWorkingHours = workingHours;
    mAddress = address;
    mWebsite = website;
    mComplexType = complexType;
    mComplexFinancing = complexFinancing;
    mComplexTypeID = complexTypeID;
    mComplexFinancingID = complexFinancingID;
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

/// setter address
void SportComplex::setAddress(const QString address) {
    mAddress = address;
}

/// setter website
void SportComplex::setWebsite(const QString website) {
    mWebsite = website;
}

/// setter complex type
void SportComplex::setComplexType(const QString complexType) {
    mComplexType = complexType;
}

/// setter complex financing
void SportComplex::setComplexFinancing(const QString complexFinancing) {
    mComplexFinancing = complexFinancing;
}

/// setter complex type id
void SportComplex::setComplexTypeID(const int complexTypeID) {
    mComplexTypeID = complexTypeID;
}

/// setter complex financing id
void SportComplex::setComplexFinancingID(const int complexFinancingID) {
    mComplexFinancingID = complexFinancingID;
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

/// getter address
QString SportComplex::getAddress() const {
    return mAddress;
}

/// getter website
QString SportComplex::getWebsite() const {
    return mWebsite;
}

/// getter complex type
QString SportComplex::getComplexType() const {
    return mComplexType;
}

/// getter complex financing
QString SportComplex::getComplexFinancing() const {
    return mComplexFinancing;
}

/// getter complex type id
int SportComplex::getComplexTypeID() const {
    return mComplexTypeID;
}

/// getter complex financng id
int SportComplex::getComplexFinancingID() const {
    return mComplexFinancingID;
}

