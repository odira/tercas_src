#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDateEdit;
QT_END_NAMESPACE

class PersonWidget;
class SectorWidget;
class DateSelect;


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
    PersonWidget *m_personW;
    QComboBox *m_typeCB;
    SectorWidget *m_sectorW;
    DateSelect *m_dateW;
};

#endif // MAPPERDIALOG_H
