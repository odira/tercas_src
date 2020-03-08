#include <QtWidgets>
#include <QtSql>
#include <QSqlError>
#include <QStringListModel>

#include "../model/SectorWorktimeModel.h"
#include "mapperdelegate.h"

MapperDelegate::MapperDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void MapperDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();

    switch (col)
    {

//    case SectorWorktimeModel::column_sectorpid:
//    {

//    }

    case SectorWorktimeModel::column_sector_pos:
    {
        QStringListModel *listModel = new QStringListModel;
        QStringList list;
        list << "РЛУ" << "ПК";
        listModel->setStringList(list);

        QComboBox *combo = qobject_cast < QComboBox * > (editor);
        Q_ASSERT(combo);
        combo->setModel(listModel);

        QString data = index.data(Qt::DisplayRole).toString();
        combo->setCurrentText(data);

        break;
    }

    case SectorWorktimeModel::column_startdate:
    case SectorWorktimeModel::column_enddate:
    {
        QDateEdit *dateEdit = qobject_cast < QDateEdit * > (editor);
        Q_ASSERT(dateEdit);

        QDate date = index.data(Qt::DisplayRole).toDate();
        if (date.isNull())
            dateEdit->setDate(QDate::currentDate());
        else
            dateEdit->setDate(date);

        break;
    }

    } // switch

    QStyledItemDelegate::setEditorData(editor, index);
}

void MapperDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();
    switch (col)
    {

    case SectorWorktimeModel::column_sector_pos:
    {
        QComboBox *combo = qobject_cast < QComboBox * > (editor);
        QString data = combo->currentText();
        model->setData(index, data);

        break;
    }

    } // switch

    QStyledItemDelegate::setModelData(editor, model, index);
}
