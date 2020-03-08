#include <QtWidgets>
#include <QStyledItemDelegate>
#include <QtSql>

#include "mapperdelegate.h"
#include "declarations.h"

MapperDelegate::MapperDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void MapperDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();

    if (/* col == ad_opr ||*/
        col == ad_type  ||
        /* col == ad_intl  || */
        col == ad_department)
    {
        QComboBox *combo = qobject_cast<QComboBox*>(editor);
        QString data = combo->currentText();
        if (data.isEmpty())
            model->setData(index, QString("undefined"));
        else
            model->setData(index, data);
    }
    else if (col == ad_opr ||
             col == ad_intl)
    {
        QCheckBox *check = qobject_cast<QCheckBox *>(editor);
        if (check->isChecked())
            model->setData(index, true);
        else
            model->setData(index, false);
    }
    else if (col == ad_elevation)
    {
        QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
        QString data = QString::number(spinBox->value());
//        int data = spinBox->value();
        model->setData(index, data);
    }
    else if (col == ad_magvar)
    {
        QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox *>(editor);
        double data = spinBox->value();
        model->setData(index, data);
    }

//    int col = index.column();
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
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void MapperDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();

//    if (col == ad_opr)
//    {
//        QComboBox *combo = static_cast<QComboBox *>(editor);
//        combo->clear();

//        QSqlQuery query("SELECT unnest(enum_range(NULL::ad.t_ad_valid))");
//        while (query.next()) {
//            QString valid = query.value(0).toString().toUtf8();
//            if (valid == "undefined")
//                combo->addItem(QString::null);
//            else
//                combo->addItem(valid);
//        }

//        QString data = index.model()->data(index, Qt::EditRole).toString().toUtf8();
//        combo->setCurrentText(data);
//    }
    if (col == ad_type)
    {
        QComboBox *combo = static_cast<QComboBox *>(editor);
        combo->clear();

        QSqlQuery query("SELECT unnest(enum_range(NULL::ad.t_ad_type))");
        while (query.next()) {
            QString valid = query.value(0).toString().toUtf8();
            if (valid == "undefined")
                combo->addItem(QString::null);
            else
                combo->addItem(valid);
        }

        QString data = index.model()->data(index, Qt::EditRole).toString().toUtf8();
        combo->setCurrentText(data);
    }
    else if (col == ad_department)
    {
        QComboBox *combo = static_cast<QComboBox *>(editor);
        combo->clear();

        QSqlQuery query("SELECT unnest(enum_range(NULL::ad.t_ad_staff))");
        while (query.next()) {
            QString valid = query.value(0).toString().toUtf8();
            if (valid == "undefined")
                combo->addItem(QString::null);
            else
                combo->addItem(valid);
        }

        QString data = index.model()->data(index, Qt::EditRole).toString().toUtf8();
        combo->setCurrentText(data);
//    }
//    else if (col == ad_intl)
//    {
////        QComboBox *combo = static_cast<QComboBox *>(editor);
////        combo->clear();

////        QSqlQuery query("SELECT unnest(enum_range(NULL::ad.t_ad_intl))");
////        while (query.next()) {
////            QString valid = query.value(0).toString().toUtf8();
////            if (valid == "undefined")
////                combo->addItem(QString::null);
////            else
////                combo->addItem(valid);
////        }

////        QString data = index.model()->data(index, Qt::EditRole).toString().toUtf8();
////        combo->setCurrentText(data);

//        bool data = index.model()->data(index, Qt::EditRole).toBool();
//        if (data == true)

    }
    else if (col == ad_elevation)
    {
        QSpinBox *spinBox = static_cast<QSpinBox *>(editor);

//        int elevation = index.model()->data(index, Qt::EditRole).toInt();
////        if (elevation == 0)
////            spinBox->setValue(-301);
////        else
//            spinBox->setValue(elevation);

        QString elevation = index.model()->data(index, Qt::EditRole).toString();
        qDebug() << "ELEVATION" << elevation;
        if (elevation.isEmpty() || elevation == "0")
            spinBox->setValue(-301);
        else
            spinBox->setValue(elevation.toInt());
    }
    else if (col == ad_magvar)
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox *>(editor);

        double magvar = index.model()->data(index, Qt::EditRole).toDouble();
        if (magvar == 0.0)
            spinBox->setValue(-51.0);
        else
            spinBox->setValue(magvar);
    }

//    int col = index.column();
//    if (col == person_icaolevelvalid ||
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
//        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
//        QDate data = index.model()->data(index, Qt::EditRole).toDate();
//        if (data.isValid())
//            lineEdit->setText(data.toString("yyyy-MM-dd"));
//        else
//            lineEdit->setText(QString(""));
//    }
//    else if (col == person_position)
//    {
//        QComboBox *combo = static_cast<QComboBox *>(editor);
//        combo->clear();
//        combo->addItem(QString::null);

////        QSqlQuery query("SELECT unnest(enum_range(NULL::person.t_position))");
//        QSqlQuery query("SELECT position,t_position FROM person.position");
//        while (query.next()) {
//            QString position = query.value(0).toString().toUtf8();
//            QString t_position = query.value(1).toString().toUtf8();
//            combo->addItem(position, t_position);
//        }
//        query.clear();

//        QString data = index.model()->data(index, Qt::EditRole).toString().toUtf8();
//        QSqlQuery query1("SELECT position,t_position FROM person.position");
//        while (query1.next()) {
//            QString position = query1.value(0).toString().toUtf8();
//            QString t_position = query1.value(1).toString().toUtf8();
//            if (t_position == data) {
//                    combo->setCurrentText(position);
//                    query1.clear();
//                    break;
//            }
//        }
//    }
//    else if (col == person_sectorgroup)
//    {
//        QComboBox *combo = static_cast<QComboBox *>(editor);
//        combo->clear();
//        combo->addItem(QString::null);

//        QSqlQuery query("SELECT unnest(enum_range(NULL::gis.t_sectorgroup))");
//        while (query.next()) {
//            QString sectorgroup = query.value(0).toString().toUtf8();
//            combo->addItem(sectorgroup);
//        }

//        QString data = index.model()->data(index, Qt::EditRole).toString().toUtf8();
//        combo->setCurrentText(data);
//    }
////    else if (col != person_positionadmittance &&
////             col != person_sectoradmittance)
////    {
////        qDebug() << "STEP 2";
////        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
////        QString data = lineEdit->text();
////        qDebug() << data;
////        if (data.isEmpty())
////            lineEdit->setText(QString(""));
////        else
////            lineEdit->setText(data);
////    }
    else
        QStyledItemDelegate::setEditorData(editor, index);
}
