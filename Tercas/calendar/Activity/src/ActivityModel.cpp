#include <QDate>
#include <QColor>
#include <QSize>

#include "ActivityModel.h"

ActivityModel::ActivityModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant ActivityModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int col = idx.column();
    if (col == path) {

        switch (role)
        {

        case Qt::DisplayRole: {
            QString coverStr = QSqlTableModel::data(index(idx.row(), path)).toString();
            if (coverStr == "ent")
                return QString(tr("ПРЕДПРИЯТИЕ"));
            else if (coverStr == "empl")
                return QString(tr("работник"));
            return coverStr;
        }

        case Qt::EditRole: {
            QString coverStr = QSqlTableModel::data(index(idx.row(), path), Qt::DisplayRole).toString();
            return coverStr;
        }

        case Qt::TextAlignmentRole:
            return Qt::AlignLeft;

        case Qt::BackgroundRole: {
            QString coverStr = QSqlTableModel::data(index(idx.row(), path)).toString();
            if (coverStr == "ent")
                return QColor("lightblue");
            else if (coverStr == "empl")
                return QColor("lightgreen");
        }

        } // switch

    } else if (col == color) {

        switch (role)
        {

        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;

        case Qt::DisplayRole: {
            QString abbrStr = QSqlTableModel::data(index(idx.row(), abbr)).toString();
            return abbrStr;
        }

        case Qt::BackgroundRole: {
            QString colorStr = QSqlTableModel::data(idx, Qt::DisplayRole).toString();
            if (colorStr.isNull())
                colorStr = QString("white");
            return QColor(colorStr);
        }

        } // switch
    }

    return QSqlTableModel::data(idx, role);
}

QVariant ActivityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section >= columnCount())
            return QVariant();

        if (role == Qt::DisplayRole)
        {

            switch (section)
            {

            case color:
                return QString(tr("Abbr"));

            case abbr:
                return QVariant();

            case activity:
                return QString(tr("Вид деятельности"));

            case note:
                return QString(tr("Примечание"));

            case path:
                return QString(tr("Производственный\nуровень"));

            } // switch

        }
        else if (role == Qt::BackgroundRole)
            return QColor("green");
        else
            return QVariant();
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
