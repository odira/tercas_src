#ifndef PERSONWIDGET_H
#define PERSONWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QSqlQueryModel;
QT_END_NAMESPACE


class PersonWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int pid READ pid WRITE setPid NOTIFY pidChanged USER true)

public:
    explicit PersonWidget(QWidget *parent = Q_NULLPTR);

    int pid() const;
    void setPid(const int &pid);

    void setEnabled(bool);
    void setFocus();

private slots:
    void surnameEdited(const QString &surname);
//    void surnameCompletionInserted()
    void surnameHighlighted(const QModelIndex &index);

signals:
    void pidChanged(int);

private:
    QLineEdit *m_surnameLineEdit;
    QLineEdit *m_nameLineEdit;
    QLineEdit *m_middlenameLineEdit;

private:
    QString m_surname;
    QString m_name;
    QString m_middlename;
    int m_pid;
    QSqlQueryModel *m_completionModel;
};

#endif // PERSONWIDGET_H
