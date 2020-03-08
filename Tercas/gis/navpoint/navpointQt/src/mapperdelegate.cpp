#include <QtWidgets>
#include <QtSql>
#include <QSqlError>

#include "mapperdelegate.h"
#include "../model/GisNavPointModel.h"

MapperDelegate::MapperDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

#include <QDebug>

void MapperDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (index.column())
    {

    case GisNavPointModel::Columns::navpoint_navpointtype:
    {
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT type FROM navpoint.type");

        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        Q_ASSERT(combo);
        combo->setModel(model);

        QString data = index.data(Qt::DisplayRole).toString();
        combo->setCurrentText(data);
//        combo->setCurrentIndex(data);

        break;
    }

    default:
        QStyledItemDelegate::setEditorData(editor, index);

    } // switch
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

    QStyledItemDelegate::setModelData(editor, model, index);
}
