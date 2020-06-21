#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QDateEdit;
class QTimeEdit;
class QPlainTextEdit;
QT_END_NAMESPACE

class PersonWidget;
class SectorWidget;


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
//    QLineEdit *m_personfullnameLE;
//    QLineEdit *m_sectorlabelLE;
    SectorWidget *m_sectorW;
    QComboBox *m_sector_posCB;
    QDateEdit *m_startdateDE;
    QTimeEdit *m_starttimeTE;
    QDateEdit *m_enddateDE;
    QTimeEdit *m_endtimeTE;
    QTimeEdit *m_intervalTE;
    QPlainTextEdit *m_notePTE;
};

#endif // MAPPERDIALOG_H
