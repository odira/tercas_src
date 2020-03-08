#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H


#include <vyborg.h>


QT_BEGIN_NAMESPACE
class QLineEdit;
class QPlainTextEdit;
QT_END_NAMESPACE

class CoordWidget;


class MapperDialog : public VyborgMapperDialog
{
    Q_OBJECT

public:
    MapperDialog(QSqlTableModel *model, QWidget *parent = Q_NULLPTR);

protected:
    virtual void createPrivateWidgets();
    virtual void layoutPrivateWidgets();
    virtual void updatePrivateWidgets();

private:
    CoordWidget *m_coordWid;
    QLineEdit *m_latLE;
    QLineEdit *m_lonLE;
    QLineEdit *m_sridLE;
    QPlainTextEdit *m_notePTE;
};

#endif // MAPPERDIALOG_H
