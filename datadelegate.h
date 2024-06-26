#ifndef DATADELEGATE_H
#define DATADELEGATE_H

#include <QStyledItemDelegate>

/// \brief Класс делегата для редактирования ячеек типа QLineEdit
class DataDelegate : public QStyledItemDelegate
{
private:
    QRegularExpression mRegExp;

public:
    /// Конструктор класса
    explicit DataDelegate(QObject* parent = nullptr, QRegularExpression regExp = QRegularExpression());

    /// Создает редактор ячейки и инициализирует его данными
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    /// Задает данные редактора ячейки на основе переданных данных
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;

    /// Сохраняет данные из редактора ячейки в модель
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

#endif // DATADELEGATE_H
