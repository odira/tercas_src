#include <QtWidgets>
#include <QStyledItemDelegate>
#include <QtSql>

#include "mapperdelegate.h"
#include "../../model/GisSectorModel.h"

#include <QDebug>

MapperDelegate::MapperDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{ }

void MapperDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    int col = index.column();
    switch (col)
    {
    case GisSectorModel::sector_freq:
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        QString freqStr = lineEdit->text();
        if (freqStr.isEmpty())
            model->setData(index, QVariant());
        else
            model->setData(index, freqStr);

        break;
    }
    case GisSectorModel::sector_phone:
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        QString phoneStr = lineEdit->text();
        if (phoneStr.isEmpty()) {
            model->setData(index, QVariant());
        } else {
            model->setData(index, phoneStr);
        }

        break;
    }
    case GisSectorModel::sector_npsdz:
    case GisSectorModel::sector_npspdz:
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        QString npsStr = lineEdit->text();
        if (npsStr.isEmpty()) {
            model->setData(index, QVariant());
        } else {
            model->setData(index, npsStr);
        }

        break;
    }
    }

//    switch (col) {
//    case sector_label:
//        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
//        QString data = lineEdit->text();
//        qDebug() << "DATA" << data;
//        if (data.isEmpty())
//            model->setData(index, QVariant());
//        else
//            model->setData(index, data);

//        break;
//    }

//    if (col == person_uservalid) {

//    }

//    if (col == person_tabnum ||
//            col == person_shift ||
//            col == person_class ||
//            col == person_icaolevel ||
//            col == person_licencenum)
//    {
//        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
//        QString data = lineEdit->text();
//        if (data.isEmpty())
//            model->setData(index, QVariant());
//        else
//            model->setData(index, data.toInt());
//    }
//    else if (col == person_icaolevelvalid ||
//             col == person_licencevalid ||
////             col == person_stazh ||
////             col == person_postup ||
//             col == person_medicalvalid ||
//             col == person_kpkrp ||
//             col == person_kpksd ||
//             col == person_kpkdi ||
//             col == person_kpkfact ||
//             col == person_kpkplan ||
//             col == person_kpkompfact ||
//             col == person_kpkompplan)
//    {
//        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
//        QString data = lineEdit->text();
//        if (data.isEmpty())
//            model->setData(index, QVariant());
//        else
//            model->setData(index, data);
//    }
//    else if (col == person_position)
//    {
//        QComboBox *combo = qobject_cast<QComboBox*>(editor);
//        QString data = combo->currentText();

//        QSqlQuery query("SELECT position,t_position FROM person.position");
//        while (query.next()) {
//            QString position = query.value(0).toString().toUtf8();
//            QString t_position = query.value(1).toString().toUtf8();
//            if (position == data) {
//                model->setData(index, t_position);
//                query.clear();
//                return;
//            }
//        }

//        model->setData(index, data);
//        query.clear();
//    }
//    else if (col == person_sectorgroup)
//    {
//        QComboBox *combo = qobject_cast<QComboBox*>(editor);
//        QString data = combo->currentText();
//        model->setData(index, data);
//    }
//    else

    QStyledItemDelegate::setModelData(editor, model, index);
}

void MapperDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    int col = index.column();
    switch (col)
    {
    case GisSectorModel::sector_freq:
    {
        QString freqStr = index.model()->data(index, Qt::DisplayRole).toString();

        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        lineEdit->setText(freqStr);

        break;
    }
    case GisSectorModel::sector_phone:
    {
        QString phoneStr = index.model()->data(index, Qt::DisplayRole).toString();

        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        lineEdit->setText(phoneStr);

        break;
    }
    case GisSectorModel::sector_npsdz:
    case GisSectorModel::sector_npspdz:
    {
        QString npsStr = index.model()->data(index, Qt::DisplayRole).toString();

        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        lineEdit->setText(npsStr);

        break;
    }
    }

    QStyledItemDelegate::setEditorData(editor, index);
}
