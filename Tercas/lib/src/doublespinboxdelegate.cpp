#include <QtWidgets>

#include "doublespinboxdelegate.h"

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

QWidget * DoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setMinimum(0.0);
    editor->setMaximum(180.00000);
    editor->setDecimals(5);

    return editor;
}

void DoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();

    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox *>(editor);
    doubleSpinBox->setValue(value);
}

void DoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox *>(editor);
    doubleSpinBox->interpretText();
    double value = doubleSpinBox->value();

    model->setData(index, value, Qt::EditRole);
}
