#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include <QStyledItemDelegate>

class DoubleSpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    DoubleSpinBoxDelegate(QObject *parent = 0);

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // DOUBLESPINBOXDELEGATE_H
