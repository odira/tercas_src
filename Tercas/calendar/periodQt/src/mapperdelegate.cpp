#include <QtWidgets>
#include <QtSql>
#include <QSqlError>


#include "mapperdelegate.h"
//#include "../model/EmplSheduleIntervalModel.h"
#include "EmplSheduleIntervalModel.h"
#include "DateSelect.h"


MapperDelegate::MapperDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{ }

//#include <QDebug>
void MapperDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();
    switch (col)
    {

//    case column_personfullname:
//    {
////        QString data = index.data(Qt::DisplayRole).toString();
////        combo->setCurrentText(data);

//        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
//        Q_ASSERT(lineEdit);
//        lineEdit->setText(index.model()->data(index).toString());

////        int personpid = index.data(Qt::EditRole).toInt();
////        QString queryString = QString("SELECT surname FROM person.vw_person WHERE pid = %1").arg(personpid);
////        qDebug() << queryString << index.model()->data(index).toString();
////        QSqlQuery query(queryString);
////        while (query.next()) {
////            QString surname = query.value(0).toString();
////            lineEdit->setText(surname);
////        }

////        QSqlQueryModel *model = new QSqlQueryModel;
////        model->setQuery("SELECT surname FROM person.vw_person where surname ilike '%еп%'");

////        QSqlTableModel *model = (QSqlTableModel*)index.model();

////        QComboBox *combo = qobject_cast<QComboBox *>(editor);
////        Q_ASSERT(combo);
////        combo->setModel(model);
////        combo->setModelColumn(column_personfullname);

//        break;
//    }

////    case column_activity_pid:

    case EmplSheduleIntervalModel::Columns::column_activity_activity:
    {
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT activity FROM calendar.vw_activity");

        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        Q_ASSERT(combo);
        combo->setModel(model);

        QString data = index.data(Qt::EditRole).toString();
        combo->setCurrentText(data);

        break;
    }

    case EmplSheduleIntervalModel::Columns::column_start_date:
    case EmplSheduleIntervalModel::Columns::column_end_date:
    {
        DateSelect *calDay_ = qobject_cast<DateSelect *>(editor);
        Q_ASSERT(calDay_);

        qDebug() << "1";
        QDate data = index.data(Qt::EditRole).toDate();
        calDay_->setDate(data);
        calDay_->show();
        qDebug() << "2";

        break;
    }

//    case column_noteru:
//    {
//        QPlainTextEdit *plainTextEditor = qobject_cast<QPlainTextEdit *>(editor);
//        Q_ASSERT(plainTextEditor);

//        QString data = index.data(Qt::EditRole).toString();
//        plainTextEditor->setPlainText(data);

//        break;

    } // switch (col)

//    default:
        QStyledItemDelegate::setEditorData(editor, index);
//        break;
//    }
}

#include <QDebug>
void MapperDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();
    switch (col)
    {

//    case column_personfullname:
//    {
//        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
//        QString surname = lineEdit->text();

//        QString queryString = QString("SELECT pid FROM person.vw_person WHERE surname ilike '%%1%' ").arg(surname);
//        QSqlQuery query(queryString);
//        while (query.next()) {
//            int personpid = query.value(0).toInt();
//            QModelIndex personPidIndx = model->index(index.row(), column_personpid);
//            model->setData(personPidIndx, personpid, Qt::EditRole);
//        }

//        break;
//    }

//    case column_activity_:
    case EmplSheduleIntervalModel::Columns::column_activity_activity:
    {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        QString activity = combo->currentText();

        QString queryString = QString("SELECT pid FROM calendar.vw_activity WHERE activity = '%1' ")
                .arg(activity);
        QSqlQuery query(queryString);
        while (query.next()) {
            int activitypid = query.value(0).toInt();
            QModelIndex activityPidIndx = model->index(index.row(), EmplSheduleIntervalModel::Columns::column_activity_pid);
            model->setData(activityPidIndx, activitypid, Qt::EditRole);
        }

        break;
    }

    case EmplSheduleIntervalModel::Columns::column_start_date:
    case EmplSheduleIntervalModel::Columns::column_end_date:
    {
        DateSelect *calDay_ = qobject_cast<DateSelect *>(editor);
        Q_ASSERT(calDay_);

        QDate data = calDay_->date();
        model->setData(index, data);

        break;
    }

//    case column_noteru:
//    {
//        QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit *>(editor);
//        Q_ASSERT(plainTextEdit);

//        QString data = plainTextEdit->toPlainText();
//        model->setData(index, data);

//        break;
//    }

    } // switch (col)

    QStyledItemDelegate::setModelData(editor, model, index);
}
