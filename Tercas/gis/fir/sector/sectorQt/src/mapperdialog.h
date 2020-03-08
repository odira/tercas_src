#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QCheckBox;
//class QPushButton;
//class QColorDialog;
QT_END_NAMESPACE

class SectorPidArrayWidget;
class NodePidArrayTableWidget;
class ColorButton;
class ColorWidget;

class MapperDialog : public VyborgMapperDialog
{
    Q_OBJECT

public:
    MapperDialog(QSqlTableModel *model, QWidget *parent = 0);

protected:
    virtual void createPrivateWidgets();
    virtual void layoutPrivateWidgets();
    virtual void updatePrivateWidgets();

private: // Visible widgets
    QLineEdit *m_pidLE;
    SectorPidArrayWidget *m_sectorpidarrW;
    QLineEdit *m_nameLE;
    QCheckBox *m_compoundCB;
    QLineEdit *m_freqLE;
    NodePidArrayTableWidget *m_nodeArrayW;
    QLineEdit *m_phoneLE;
    QLineEdit *m_npsdzLE;
    QLineEdit *m_npspdzLE;
//    QPushButton *m_colorPB;
    ColorButton *m_colorButton;
//    QColorDialog *m_colorDialog;
    ColorWidget *m_colorW;
};

#endif // MAPPERDIALOG_H
