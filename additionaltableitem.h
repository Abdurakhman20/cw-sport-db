#ifndef ADDITIONALTABLEITEM_H
#define ADDITIONALTABLEITEM_H

#include <QObject>

class AdditionalTableItem
{
private:
    int mID;
    QString mName;
public:
    /// Конструктор класса
    AdditionalTableItem();
    /// Конструктор с значениями
    AdditionalTableItem(const int id, const QString mName);

    /// Устанавливаем Функции Setter
    /// Setter ID
    void setID(const int id);

    /// Setter Name
    void setName(const QString name);

    /// Устанавливаем Функции Getter
    /// Getter ID
    int getID() const;

    /// Getter Name
    QString getName() const;
};

#endif // ADDITIONALTABLEITEM_H
