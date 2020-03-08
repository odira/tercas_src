#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class VyborgNavigationButtonBox;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

private:
    VyborgNavigationButtonBox *m_navigationBB;
};

#endif // DIALOG_H


