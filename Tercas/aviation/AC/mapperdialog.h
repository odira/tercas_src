#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

class QLineEdit;
class QTextEdit;



class MapperDialog : public VyborgMapperDialog
{
    Q_OBJECT

public:
    MapperDialog(QSortFilterProxyModel *proxy, QWidget *parent = 0);

protected:
    virtual void createPrivateWidgets();
    virtual void layoutPrivateWidgets();
    virtual void updatePrivateWidgets();

private:
    QLineEdit *ICAOlineEdit;
    QLineEdit *IATAlineEdit;
    QLineEdit *codeRuLineEdit;
    QLineEdit *CSlineEdit;
    QLineEdit *CSruLineEdit;
    QLineEdit *AClineEdit;
    QLineEdit *ACruLineEdit;
    QTextEdit *fleetTextEdit;
    QTextEdit *noteTextEdit;
    QTextEdit *noteRuTextEdit;
    QLineEdit *countryLineEdit;
    QLineEdit *pointLineEdit;
};

#endif // MAPPERDIALOG_H
