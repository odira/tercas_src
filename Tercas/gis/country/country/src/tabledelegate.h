#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QItemDelegate>

#define DEFAULT_WIDTH 100
#define DEFAULT_HEIGHT 50
#define MARGIN 5


class ImageTableDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    ImageTableDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

//public slots:
//    void setWidth(int width);
//    void setHeight(int height);

private:
    int m_width;
    int m_height;
};

#endif // TABLEDELEGATE_H
