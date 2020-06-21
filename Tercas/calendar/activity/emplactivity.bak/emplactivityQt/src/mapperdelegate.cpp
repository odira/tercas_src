#include <QtWidgets>
#include <QtSql>
#include <QSqlError>

#include "declarations.h"
#include "mapperdelegate.h"
#include "colorwidget.h"

MapperDelegate::MapperDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void MapperDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
/* Enter code here if delegates rather than QLineEdit is used
 *
 * switch (index.column()) {
 * case month_department: {
 *     QSqlQueryModel *model = new QSqlQueryModel;
 *     model->setQuery("SELECT department FROM structure.department");
 *
 *     QComboBox *combo = qobject_cast<QComboBox *>(editor);
 *     Q_ASSERT(combo);
 *     combo->setModel(model);
 *
 *     QString data = index.data(Qt::DisplayRole).toString();
 *     combo->setCurrentText(data);
 *     break;
 * }
 * }
 */

    QStyledItemDelegate::setEditorData(editor, index);
}

#include <QDebug>
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

    int row = index.row();
    int col = index.column();

    if (col == emplactivity_pid) {
        ColorWidget *colorW = qobject_cast<ColorWidget *>(editor);
        Q_ASSERT(colorW);

        QColor color = colorW->color();
        QString colorString = color.name();
        QString abbr = colorW->abbr();

        QModelIndex colorIdx = model->index(row, emplactivity_color);
        QModelIndex abbrIdx = model->index(row, emplactivity_abbr);

        model->setData(colorIdx, colorString);
        model->setData(abbrIdx, abbr);
    }

//    switch (col) {
//    case ActivityModelColumns::noteru: {
//        QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit *>(editor);
//        Q_ASSERT(plainTextEdit);

//        QString noteruString = plainTextEdit->toPlainText();
////        QModelIndex noteruIdx = model->index(row, Columns::emplactivity_noteru);
////        model->setData(noteruIdx, noteruString);
//        model->setData(index, noteruString);
//        break; }
//    }

    QStyledItemDelegate::setModelData(editor, model, index);
}
