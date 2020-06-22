#include <QDate>
#include <QColor>
#include <QSize>

#include "../emplactivityQt/src/declarations.h"
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
    if (col == emplactivity_color)
    {
        switch (role) {
        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;
            break;

        case Qt::DisplayRole: {
            QString abbrStr = QSqlTableModel::data(index(idx.row(), emplactivity_abbr)).toString();
            return abbrStr;
            break;
        }
        case Qt::BackgroundRole: {
            QString colorStr = QSqlTableModel::data(idx, Qt::DisplayRole).toString();
            if (colorStr.isNull())
                colorStr = QString("white");
            return QColor(colorStr);
            break;
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
            case emplactivity_color:
                return QVariant();
                break;

            case emplactivity_abbr:
                return QString(trUtf8("Сокращение"));
                break;

            case emplactivity_emplactivity:
                return QString(trUtf8("Вид деятельности"));
                break;

            case emplactivity_noteru:
                return QString(trUtf8("Примечание"));
                break;
            } // switch (section)
        }
    }

    return QSqlTableModel::headerData(section, orientation, role);
}
