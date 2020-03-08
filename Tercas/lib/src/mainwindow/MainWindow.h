#ifndef VYBORGMAINWINDOW_H
#define VYBORGMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QPushButton;
class QSqlTableModel;
class QTableView;
QT_END_NAMESPACE

class VyborgMapperDialog;
class VyborgFilterDialog;
class VyborgSortDialog;
class VyborgAboutDialog;
class VyborgMainDialogControlButtonBox;

//class VyborgMonthCalendarNavigationToolbar;

class VyborgMainWindow : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO("author", "Vladimir Ilin")

public:
    explicit VyborgMainWindow(QWidget *parent = 0);

    QPushButton* addButton(const QString &text);

protected:
    virtual void setupModel() = 0;
    virtual void setupView() = 0;
    virtual void setupMapperDialog() = 0;
    virtual void setupFilterDialog() = 0;
    virtual void setupSortDialog()  = 0;

private slots:
    void add();
    void remove();
    void update();
    void about();
    void showMapperDialog();
    void showFilterDialog();
    void showSortDialog();

public:
    QSqlTableModel *m_model;
    QTableView *m_view;
    VyborgMapperDialog *m_mapperDialog;
    VyborgFilterDialog *filterDialog_;
    VyborgSortDialog *sortDialog_;
    VyborgAboutDialog *aboutDialog_;
    VyborgMainDialogControlButtonBox *m_controlButtonBox;

//    VyborgMonthCalendarNavigationToolbar *m_monthCalNavToolBar;
};

#endif // VYBORGMAINWINDOW_H
