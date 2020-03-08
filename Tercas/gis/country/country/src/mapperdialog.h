#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class MapperDialog : public VyborgMapperDialog
{
    Q_OBJECT

public:
    MapperDialog(QSqlTableModel *model, QWidget *parent = 0);

protected:
    virtual void createPrivateWidgets();
    virtual void layoutPrivateWidgets();
    virtual void updatePrivateWidgets();

private:
    // Visual elements
    QLineEdit *m_nameLE;
    QLineEdit *m_nameruLE;
    QLineEdit *m_nameshortLE;
    QLineEdit *m_nameshortruLE;
    QLineEdit *m_iso3166code2LE;
    QLineEdit *m_iso3166code3LE;
    QLineEdit *m_iso3166codenLE;
    QLineEdit *m_noteLE;
    QLineEdit *m_noteruLE;
};

#endif // MAPPERDIALOG_H
