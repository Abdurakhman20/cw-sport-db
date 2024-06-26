#include "datadelegate.h"

#include <QLineEdit>
#include <QRegularExpressionValidator>

DataDelegate::DataDelegate(QObject* parent, QRegularExpression regExp)
    : QStyledItemDelegate(parent)
{
    mRegExp = regExp;
}

/// Создаём виджет редактора значения, который будет использоваться вместо
/// стандартного QLineEdit
QWidget* DataDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QLineEdit* editor = new QLineEdit(parent);
    QRegularExpressionValidator* validator =
        new QRegularExpressionValidator(this->mRegExp, editor);
    editor->setValidator(validator);
    return editor;
}

/// Передаём значение от модели QTableWidget в редактор QLineEdit,
/// когда пользователь начинает редактирование данных в ячейке S
void DataDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(value);
}

/// Передаёт значение от редактора в модель,
/// когда пользователь закончил ввод и нажал Enter
void DataDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    QString value = lineEdit->text();
    model->setData(index, value, Qt::EditRole);
}
