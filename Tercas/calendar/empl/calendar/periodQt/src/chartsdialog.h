#ifndef CHARTSDIALOG_H
#define CHARTSDIALOG_H

#include <vyborg.h>

class ChartsDialog : public VyborgChartsDialog
{
    Q_OBJECT

public:
    ChartsDialog(QSqlTableModel *model = 0, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

protected:
    virtual void createCharts() Q_DECL_OVERRIDE;
};

#endif // CHARTSDIALOG_H
