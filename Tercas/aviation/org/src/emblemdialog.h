#ifndef EMBLEMDIALOG_H
#define EMBLEMDIALOG_H

#include <QDialog>

namespace Ui {
class EmblemDialog;
}

class EmblemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmblemDialog(const int &id, QWidget *parent = 0);
    ~EmblemDialog();

private slots:
    void on_addButtonClicked();

private:
    Ui::EmblemDialog *ui;
    int m_id;
};

#endif // EMBLEMDIALOG_H
