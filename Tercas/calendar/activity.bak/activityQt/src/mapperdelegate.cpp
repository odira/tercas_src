#include <QtWidgets>
#include <QtSql>
#include <QSqlError>

#include "../model/ActivityModel.h"
#include "mapperdelegate.h"
#include "colorwidget.h"

MapperDelegate::MapperDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void MapperDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (index.column())
    {

    case ActivityModel::Columns::path:
    {
        QStandardItemModel *model = new QStandardItemModel(2, 2);

        QStandardItem *item = new QStandardItem(QString("empl"));
        model->setItem(0, 0, item);

        item = new QStandardItem(QString("ent"));
        model->setItem(1, 0, item);

        item = new QStandardItem(QString("Работник"));
        model->setItem(0, 1, item);

        item = new QStandardItem(QString("ПРЕДПРИЯТИЕ"));
        model->setItem(1, 1, item);


        QComboBox *combo = qobject_cast < QComboBox* > (editor);
        Q_ASSERT(combo);

        combo->setModel(model);
        combo->setModelColumn(1);

        QString coverStr = index.data(Qt::DisplayRole).toString();
        combo->setCurrentText(coverStr);

        break;
    }

    default:
        QStyledItemDelegate::setEditorData(editor, index);

    } // switch
}

#include <QDebug>
void MapperDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();

    switch (col)
    {

    case ActivityModel::Columns::pid:
    {
        ColorWidget *colorW = qobject_cast < ColorWidget* > (editor);
        Q_ASSERT(colorW);

        QColor color = colorW->color();
        QString colorString = color.name();
        QString abbr = colorW->abbr();

        qDebug() << color.name() << abbr;

        QModelIndex colorIdx = model->index(row, ActivityModel::Columns::color);
        QModelIndex abbrIdx = model->index(row, ActivityModel::Columns::abbr);

        model->setData(colorIdx, colorString);
        model->setData(abbrIdx, abbr);

        break;
    }

    case ActivityModel::Columns::path:
    {
        QComboBox *combo = qobject_cast < QComboBox* > (editor);
        Q_ASSERT(combo);

        QString data = combo->currentText();
        if (data == "Работник")
            model->setData(index, "empl");
        else if (data == "ПРЕДПРИЯТИЕ")
            model->setData(index, "ent");

        break;
    }

    default:
        QStyledItemDelegate::setModelData(editor, model, index);

    } // switch


//    if (col == activity_pid)
//    {
//        ColorWidget *colorW = qobject_cast< ColorWidget * >(editor);
//        Q_ASSERT(colorW);

//        QColor color = colorW->color();
//        QString colorString = color.name();
//        QString abbr = colorW->abbr();

//        QModelIndex colorIdx = model->index(row, activity_color);
//        QModelIndex abbrIdx = model->index(row, activity_abbr);

//        model->setData(colorIdx, colorString);
//        model->setData(abbrIdx, abbr);
//    }

//    switch (col) {
//    case ActivityModelColumns::noteru: {
//        QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit *>(editor);
//        Q_ASSERT(plainTextEdit);

//        QString noteruString = plainTextEdit->toPlainText();
////        QModelIndex noteruIdx = model->index(row, Columns::activity_noteru);
////        model->setData(noteruIdx, noteruString);
//        model->setData(index, noteruString);
//        break; }
//    }

}
