#ifndef ORGDIALOG_H
#define ORGDIALOG_H

#include <QDialog>

class QTableWidget;
class QPushButton;


class OrgDialog : public QDialog
{
    Q_OBJECT

public:
    OrgDialog(QWidget *parent = 0);

    void setRetValue(const QString &retValue);
    QString retValue() const;

private slots:
    void on_acceptButtonClicked();
    void on_tableWidgetCellClicked(int row, int column);

private:
    QString m_retValue;

    QTableWidget *m_tableWidget;
    QPushButton  *m_acceptButton;
};

#endif // ORGDIALOG_H
