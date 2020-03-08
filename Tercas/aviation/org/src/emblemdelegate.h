#ifndef EMBLEMDELEGATE_H
#define EMBLEMDELEGATE_H

#include <QStyledItemDelegate>


class EmblemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit EmblemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // EMBLEMDELEGATE_H
