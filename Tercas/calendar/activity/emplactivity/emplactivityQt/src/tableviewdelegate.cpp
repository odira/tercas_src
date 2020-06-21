#include <QtWidgets>
#include <QQuickWidget>
#include <QQmlContext>
#include <QSqlTableModel>
#include <QAbstractItemModel>

//#include "declarations.h"
#include "../model/EmplActivityModel.h"
#include "tableviewdelegate.h"

TableViewDelegate::TableViewDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{ }

#include <QDebug>
void TableViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    if (col == EmplActivityModel::Columns::activity_pid)
    {
//        QSqlTableModel *model = qobject_cast<QSqlTableModel*>(index.model());
//        QModelIndex indx = model->index(row, emplactivity_color);
//        QString colorStr = model->data(indx).toString();
//        qDebug() << colorStr;

        qDebug() << index.data();
        QString abbrStr = index.model()->data(index.model()->index(row, EmplActivityModel::Columns::activity_color)).toString();

        QQuickWidget *qqwid = new QQuickWidget;
        qqwid->setSource(QStringLiteral("qrc:qml/EmplActivity.qml"));
        qqwid->rootContext()->setContextProperty("abbr", abbrStr);
        if (option.state == QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());
        QPixmap map =  qqwid->grab();
        painter->drawPixmap(option.rect.x(),option.rect.y(),map);

    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

QSize TableViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return QSize(35, 35);
}
