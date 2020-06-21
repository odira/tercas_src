#include <QDate>
#include <QColor>
#include <QSize>

#include "EmplActivityModel.h"

EmplActivityModel::EmplActivityModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant EmplActivityModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int col = idx.column();
    if (col == activity_color)
    {
        switch (role) {
        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;
            // break;

        case Qt::DisplayRole: {
            QString abbrStr = QSqlTableModel::data(index(idx.row(), activity_abbr)).toString();
            return abbrStr;
            // break;
        }
        case Qt::BackgroundRole: {
            QString colorStr = QSqlTableModel::data(idx, Qt::DisplayRole).toString();
            if (colorStr.isNull())
                colorStr = QString("white");
            return QColor(colorStr);
            // break;
        }
        }
    }

    return QSqlTableModel::data(idx, role);
}

QVariant EmplActivityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (section >= columnCount())
            return QVariant();

        if (role == Qt::DisplayRole)
        {
            switch (section)
            {
            case activity_color:
                return QVariant();
                // break;

            case activity_abbr:
                return QString(tr("Сокращение"));
                // break;

            case activity_activity:
                return QString(tr("Вид деятельности"));
                // break;

            case activity_note:
                return QString(tr("Примечание"));
                //break;
            } // switch (section)
        }
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
