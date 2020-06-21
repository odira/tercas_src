#include <QDate>

#include <vyborg.h>

#include "declarations.h"
#include "tablemodel.h"

TableModel::TableModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
//    int col = index.column();
//    if (col == activity_color || col == activity_abbr)
//    {
////        Qt::ItemFlags flags_ = Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemNeverHasChildren;
//        Qt::ItemFlags flags_ = Qt::ItemIsEnabled;
//        return flags_;
//    }
//    else
//    {
        return QSqlTableModel::flags(index);
//    }
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ColumnsNumber;
}

QVariant TableModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid()) {
        return QVariant();
    }

    int col = idx.column();
    switch (col)
    case activity_color:
    {
        if (role == Qt::TextAlignmentRole)
        {
            return Qt::AlignCenter;
        }
        else if (role == Qt::DisplayRole)
        {
            QString abbr = QSqlTableModel::data(index(idx.row(), activity_abbr)).toString();
            return abbr;
        }
        else if (role == Qt::BackgroundRole)
        {
            QString colorString = QSqlTableModel::data(idx, Qt::DisplayRole).toString();
            if (!colorString.isNull()) {
                return QColor(colorString);
            } else {
                return QColor("white");
            }
        }
        else if (role == Qt::SizeHintRole)
        {
            return QSize(38, 20);
        }

        break;
    } // activity_color

    return QSqlTableModel::data(idx, role);
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section >= columnCount()) {
            return QVariant();
        }

        if (role == Qt::DisplayRole) {
            switch (section) {
            case activity_color:
//                return QString(trUtf8("Цвет"));
                return QString();
                break;
            case activity_abbr:
                return QString(trUtf8("Сокращение"));
                break;
            case activity_activity:
                return QString(trUtf8("Вид деятельности"));
                break;
            case activity_noteru:
                return QString(trUtf8("Примечание"));
                break;
            }
        }
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
