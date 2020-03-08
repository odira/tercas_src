#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <QDialog>

class RelationalTableModel;
QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
class QLineEdit;
QT_END_NAMESPACE


class MapperDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapperDialog(RelationalTableModel *model, int indx, QWidget *parent = 0);

private slots:
    void save();

private:
    RelationalTableModel *m_model;
    QDataWidgetMapper *m_mapper;
};

#endif // MAPPERDIALOG_H
