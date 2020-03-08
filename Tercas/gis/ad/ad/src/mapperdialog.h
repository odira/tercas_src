#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QSpinBox;
class QCheckBox;
class QDoubleSpinBox;
class QPlainTextEdit;
QT_END_NAMESPACE

class NodeWidget;
class RWWidget;

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
    QCheckBox      *m_oprCheckBox;
    QCheckBox      *m_intlCheckBox;
    QComboBox      *m_departmentComboBox;

    QLineEdit      *m_countryLE;
    QLineEdit      *m_cityruLE;
    QLineEdit      *m_nameruLE;
    QLineEdit      *m_nameLE;
    QLineEdit      *m_indxLE;
    QLineEdit      *m_reglamentLE;
    QLineEdit      *m_emailLE;
    QLineEdit      *m_webLE;
    QSpinBox       *m_elevationSB;
    QDoubleSpinBox *m_magvarDSB;
    QComboBox      *m_typeCB;
    QPlainTextEdit *m_notePTE;
    NodeWidget     *m_nodeWid;
    RWWidget       *m_rwWid;
};

#endif // MAPPERDIALOG_H
