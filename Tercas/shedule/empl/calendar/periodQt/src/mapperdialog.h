#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <QDate>

#include <vyborg.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QSpinBox;
class QPlainTextEdit;
QT_END_NAMESPACE

class PersonWidget;
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

private slots:
    void startDateChanged(const QDate &date);
    void endDateChanged(const QDate &date);

private:
    PersonWidget *m_personWidget;
    QComboBox *m_activityComboBox;
    DateSelect *m_startDateSelect;
    DateSelect *m_endDateSelect;
    QSpinBox *m_intervalAllSpinBox;
    QSpinBox *m_intervalWorkSpinBox;
    QPlainTextEdit *m_notePTE;
};

#endif // MAPPERDIALOG_H
