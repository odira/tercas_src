#ifndef VYBORGCHARTSDIALOG_H
#define VYBORGCHARTSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QSqlTableModel;
class QVBoxLayout;
QT_END_NAMESPACE

class VyborgChartsDialog : public QDialog
{
    Q_OBJECT

public:
    VyborgChartsDialog(QSqlTableModel *model = 0, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

    QVBoxLayout* layout() const;

protected:
    virtual void createCharts() = 0;

public:
//    // non-visual Qt elements
    QSqlTableModel *m_model;

//    // visual Qt elements
    QVBoxLayout *m_chartsLayout;
};

#endif // VYBORGCHARTSDIALOG_H
