#ifndef VYBORGMAPPERDIALOG_H
#define VYBORGMAPPERDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QSqlTableModel;
class QDataWidgetMapper;
class QVBoxLayout;
QT_END_NAMESPACE

class VyborgMapperControlButtonBox;
class VyborgNavigationButtonBox;

class VyborgMapperDialog : public QDialog
{
    Q_OBJECT

public:
    VyborgMapperDialog(QSqlTableModel *model, QWidget *parent = 0);

    QDataWidgetMapper* mapper();
    QVBoxLayout* layout();

    enum State { Normal, Edit, Add };
    Q_ENUM( State )
    void setState(State state);
    State state() const;

public slots:
    void setCurrentRow(int row);

protected:
    virtual void createPrivateWidgets() = 0;
    virtual void layoutPrivateWidgets() = 0;
    virtual void updatePrivateWidgets() = 0;

private slots:
    void edit();
    void submit();
    void revert();
    void close();

private:
    void updateControlWidgets();

private: // widgets
    VyborgMapperControlButtonBox *m_controlButtonBox;
    VyborgNavigationButtonBox *m_navButtonBox;
    QVBoxLayout *m_privateWidgetsLayout;

private: // non-visual Qt elements
    QSqlTableModel *m_model;
    QDataWidgetMapper *m_mapper;

private: // non-visual variables
    State m_state;
};

#endif // VYBORGMAPPERDIALOG_H
