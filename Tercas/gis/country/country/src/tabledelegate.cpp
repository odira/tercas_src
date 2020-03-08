#include <QtWidgets>
#include <QSql>

#include "tabledelegate.h"
#include "declarations.h"
#include "imagewidget.h"

ImageTableDelegate::ImageTableDelegate(QObject *parent) :
    QItemDelegate(parent), m_width(DEFAULT_WIDTH), m_height(DEFAULT_HEIGHT)
{
}

#include <QDebug>
void ImageTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QRect rect(option.rect.x() + MARGIN,
               option.rect.y() + MARGIN,
               m_width - MARGIN * 2,
               m_height- MARGIN * 2);


    QSortFilterProxyModel *proxy = (QSortFilterProxyModel *) index.model();
    QModelIndex indx = proxy->index(index.row(), country_name);
    QString nnn = proxy->data(indx).toString();
//    qDebug() << nnn;

    QString fileName = IMAGE_DIR;
    fileName.append(nnn);
    fileName.append("/flag/flag.gif");
    qDebug() << fileName;

    if (!fileName.isEmpty())
    {
        QImage image = QImage(fileName).scaled(rect.width(), rect.height(), Qt::KeepAspectRatio);
        painter->drawImage(rect.x(), rect.y(), image);
        painter->drawRect(rect.x(), rect.y(), image.width(), image.height());

//        ImageWidget *image = new ImageWidget;
//        image->setFileName(fileName);
////        painter->drawRect(50, 50, image);
//        painter->drawRect(50, 50, 40, 40);
    }
    else
    {
        QString text(trUtf8("No Flag"));
        painter->drawText(rect, Qt::AlignCenter, text);
    }

    painter->restore();
}

QSize ImageTableDelegate::sizeHint(const QStyleOptionViewItem & /* option */, const QModelIndex & /*index */) const
{
    QSize size(m_width, m_height);
    return size;
}

//void ImageTableDelegate::setWidth(int width)
//{
//    m_width = width;
//}

//void ImageTableDelegate::setHeight(int height)
//{
//    m_height = height;
//}
