#include <QtWidgets>
#include <QtSql>

#include "emblemdelegate.h"
#include "declarations.h"

#include <QDebug>


EmblemDelegate::EmblemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void EmblemDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    int id = model->data(model->index(index.row(), org_id)).toInt();
    QByteArray emblem;

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("SELECT emblem FROM org WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    while (query.next()) {
        int fieldIndx = query.record().indexOf("emblem");
        emblem = query.value(fieldIndx).toByteArray();
    }
    QSqlDatabase::database().commit();

    if (emblem.size() <= 0) {
        qDebug() << "ERROR: emblem is 0 size";
        return;
    }


    QRect mainRect = option.rect;
    QPixmap pixmap;
    pixmap.loadFromData(emblem);

    if (option.state & QStyle::State_Selected) {
        pixmap = pixmap.scaled(mainRect.width() * 9/10, mainRect.height() * 9/10,
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation);
    } else {
        pixmap = pixmap.scaled(mainRect.width() * 3/10, mainRect.height() * 3/10,
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation);
    }

    painter->drawPixmap(mainRect.x() + (mainRect.width() - pixmap.width()) /2,
                        mainRect.y() + (mainRect.height() - pixmap.height()) /2,
                        pixmap);
}

QSize EmblemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    return QSize(120, 120);
}
