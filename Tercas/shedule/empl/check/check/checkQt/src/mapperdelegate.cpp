#include <QtWidgets>
#include <QtSql>
#include <QSqlError>

#include "../model/EmplSectorCheckModel.h"

#include "mapperdelegate.h"
#include "SectorWidget.h"

MapperDelegate::MapperDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void MapperDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    int col = index.column();
    switch (col)
    {
    case EmplSectorCheckModel::Columns::column_sectorpid:
    {
        SectorWidget *sectorW = qobject_cast<SectorWidget *>(editor);
        Q_ASSERT(sectorW);

        int sectorpid = index.data().toInt();
        if (sectorpid == 0)
            sectorpid = 11;

        sectorW->setPid(sectorpid);

        break;
     }
    case EmplSectorCheckModel::Columns::column_type:
    {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        Q_ASSERT(combo);

        QString sectorcheckStr = index.data().toString();
        if (sectorcheckStr.isEmpty()) {
            combo->setCurrentText(QString());
        } else {
            combo->setCurrentText(sectorcheckStr);
        }

        break;
    }
    }

    QStyledItemDelegate::setEditorData(editor, index);
}

void MapperDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
/* Enter code here if delegates rather than QLineEdit is used
 *
 *  switch (index.column()) {
 *  case month_department: {
 *     QComboBox *combo = qobject_cast<QComboBox *>(editor);
 *     QString data = combo->currentText();
 *     if (data == "unassigned")
 *         model->setData(index, QVariant());
 *     else
 *         model->setData(index, data);
 *     break;
 *  }
 *  }
 */

    if (!index.isValid()) {
        return;
    }

    int col = index.column();
    switch (col)
    {

    case EmplSectorCheckModel::Columns::column_type:
    {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        Q_ASSERT(combo);

        QString sectorcheckStr = combo->currentText();
        model->setData(index, sectorcheckStr);

        break;
    }

    case EmplSectorCheckModel::Columns::column_sectorpid:
    {
        SectorWidget *sectorW = qobject_cast<SectorWidget *>(editor);
        Q_ASSERT(sectorW);

        int sectorpid = sectorW->pid();
        model->setData(index, sectorpid);

        break;
    }

    default:
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
    }
}
