#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

class QLineEdit;
class QDateEdit;
class QTextEdit;


class EditDialog : public QDialog
{
    Q_OBJECT

public:
    EditDialog(int id, QWidget *parent = 0);

private slots:
    void accept();
    void reject();
    void on_fileButtonClicked();
    void on_sqliteButtonClicked();
    void on_addOrgButtonClicked();

private:
    QLineEdit *m_docLineEdit;
    QLineEdit *m_versionLineEdit;
    QLineEdit *m_orgLineEdit;
    QLineEdit *m_issueNumLineEdit;
    QDateEdit *m_issueDateEdit;
    QTextEdit *m_noteTextEdit;
    QLineEdit *m_tagsLineEdit;

    QString m_fileName;
    int m_id;
};

#endif // EDITDIALOG_H
