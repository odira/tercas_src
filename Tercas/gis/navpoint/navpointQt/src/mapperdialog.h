#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QPlainTextEdit;
QT_END_NAMESPACE

class NodeWidget;

class MapperDialog : public VyborgMapperDialog
{
    Q_OBJECT

public:
    MapperDialog(QSqlTableModel *model, QWidget *parent = Q_NULLPTR);

protected:
    virtual void createPrivateWidgets() Q_DECL_OVERRIDE;
    virtual void layoutPrivateWidgets() Q_DECL_OVERRIDE;
    virtual void updatePrivateWidgets() Q_DECL_OVERRIDE;

private:
    QLineEdit *m_navpointLE;
    QLineEdit *m_identLE;
    QComboBox *m_navpointtypeCB;
    QPlainTextEdit *m_noteruPTE;
    NodeWidget *m_nodeW;
};

#endif // MAPPERDIALOG_H
