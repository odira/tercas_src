#ifndef VYBORGMAINDIALOG_H
#define VYBORGMAINDIALOG_H

#include <QDialog>

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

class VyborgMainDialog : public QDialog
{
    Q_OBJECT
    Q_CLASSINFO("author", "Vladimir Ilin")

public:
    VyborgMainDialog(QWidget *parent = 0);

    void setTitle(const QString &title);
    QPushButton* addButton(const QString &text);

protected:
    virtual void setupModel() = 0;
    virtual void setupView() = 0;
    virtual void setupMapperDialog() = 0;
    virtual void setupFilterDialog() = 0;
    virtual void setupSortDialog() = 0;

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
};

#endif // VYBORGMAINDIALOG_H
