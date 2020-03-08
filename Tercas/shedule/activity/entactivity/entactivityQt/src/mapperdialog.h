#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

QT_BEGIN_NAMESPACE
class QDateEdit;
class QLineEdit;
class QPlainTextEdit;
QT_END_NAMESPACE

class AbbrColorWidget;

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
    AbbrColorWidget *m_abbrcolorW;
    QLineEdit *m_colorLE;
    QLineEdit *m_abbrLE;
    QLineEdit *m_entactivityLE;
    QPlainTextEdit *m_noteruPTE;
};

#endif // MAPPERDIALOG_H
