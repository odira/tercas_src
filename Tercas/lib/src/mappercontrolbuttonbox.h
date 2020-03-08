#ifndef VYBORGMAPPERCONTROLBUTTONBOX_H
#define VYBORGMAPPERCONTROLBUTTONBOX_H

#include <QDialogButtonBox>

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class VyborgMapperControlButtonBox : public QDialogButtonBox
{
    Q_OBJECT

public:
    VyborgMapperControlButtonBox(QWidget *parent = 0);

    void setDirty(bool dirty);

private slots:
    void on_editButtonClicked();
    void on_submitButtonClicked();
    void on_revertButtonClicked();
    void on_closeButtonClicked();

signals:
    void edit();
    void submit();
    void revert();
    void close();

private:
    QPushButton *m_editButton;
    QPushButton *m_submitButton;
    QPushButton *m_revertButton;
    QPushButton *m_closeButton;

private:
    bool m_dirty;
};

#endif // VYBORGMAPPERCONTROLBUTTONBOX_H
