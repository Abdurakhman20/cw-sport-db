#include "additionaltableitem.h"

AdditionalTableItem::AdditionalTableItem()
{

}


AdditionalTableItem::AdditionalTableItem(const int id, const QString name)
{
    mID = id;
    mName = name;
}

void AdditionalTableItem::setID(const int id)
{
    mID = id;
}

void AdditionalTableItem::setName(const QString name)
{
    mName = name;
}

int AdditionalTableItem::getID() const
{
    return mID;
}

QString AdditionalTableItem::getName() const
{
    return mName;
}
