#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

//QT_BEGIN_NAMESPACE
//class QDateEdit;
//class QLineEdit;
//class QComboBox;
//QT_END_NAMESPACE

class MapperDialog : public VyborgMapperDialog
{
    Q_OBJECT

public:
    MapperDialog(QSqlTableModel *model, QWidget *parent = 0);

protected:
    virtual void createPrivateWidgets() Q_DECL_OVERRIDE;
    virtual void layoutPrivateWidgets() Q_DECL_OVERRIDE;
    virtual void updatePrivateWidgets() Q_DECL_OVERRIDE;

private:
//    QDateEdit *m_monthyearDateEdit;
//    QComboBox *m_departmentComboBox;
//    QLineEdit *m_volLineEdit;
};

#endif // MAPPERDIALOG_H
