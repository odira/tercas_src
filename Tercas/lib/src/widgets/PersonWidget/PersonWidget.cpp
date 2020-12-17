#include <QtWidgets>
#include <QtSql>

#include "PersonWidget.h"

PersonWidget::PersonWidget(QWidget *parent)
    : QWidget(parent),
      m_pid(-1)
{
    m_surnameLineEdit = new QLineEdit;
    m_nameLineEdit = new QLineEdit;
    m_middlenameLineEdit = new QLineEdit;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(2);
//    mainLayout->setMargin(0);
    mainLayout->addWidget(m_surnameLineEdit);
    mainLayout->addWidget(m_nameLineEdit);
    mainLayout->addWidget(m_middlenameLineEdit);

    setLayout(mainLayout);

    connect(m_surnameLineEdit, SIGNAL(textEdited(QString)),
            this, SLOT(surnameEdited(QString)));
}

void PersonWidget::setPid(const int &pid)
{
    if (pid != m_pid)
    {
        m_pid = pid;
        emit pidChanged(m_pid);

        QString queryString = QString("SELECT surname, name, middlename FROM person.vw_person WHERE pid=%1").arg(m_pid);
        QSqlQuery query(queryString);
        while (query.next()) {
            QString surname = query.value(0).toString();
            QString name = query.value(1).toString();
            QString middlename = query.value(2).toString();

            m_surnameLineEdit->setText(surname);
            m_nameLineEdit->setText(name);
            m_middlenameLineEdit->setText(middlename);
        }
    }
}

int PersonWidget::pid() const
{
    QString surname = m_surnameLineEdit->text();
    QString name = m_nameLineEdit->text();
    QString middlename = m_middlenameLineEdit->text();

    QString queryString = QString("SELECT pid FROM person.vw_person "
                                  "WHERE surname ILIKE '%%1%' AND name ILIKE '%%2%' AND middlename ILIKE '%%3%'")
            .arg(surname)
            .arg(name)
            .arg(middlename);
    QSqlQuery query(queryString);
    while (query.next()) {
        int pid = query.value(0).toInt();
        query.clear();
        return pid;
    }
}

void PersonWidget::setEnabled(bool enabled)
{
    if (enabled == true)
    {
        m_surnameLineEdit->setReadOnly(false);
        m_nameLineEdit->setReadOnly(false);
        m_middlenameLineEdit->setReadOnly(false);
    }
    else if (enabled == false)
    {
        m_surnameLineEdit->setReadOnly(true);
        m_nameLineEdit->setReadOnly(true);
        m_middlenameLineEdit->setReadOnly(true);
    }
}

void PersonWidget::setFocus()
{
    m_surnameLineEdit->setFocus();
}

void PersonWidget::surnameEdited(const QString &surname)
{
    m_nameLineEdit->clear();
    m_middlenameLineEdit->clear();

    QString queryString = QString("SELECT pid,surname,name,middlename FROM person.vw_person "
                                                       "WHERE surname ILIKE '%1%'")
                                                       .arg(surname);
//    QSqlQueryModel *completionModel = new QSqlQueryModel(this);
    m_completionModel = new QSqlQueryModel(this);
    m_completionModel->setQuery(queryString);

    QCompleter * completer = new QCompleter(this);
    completer->setModel(m_completionModel);
    completer->setCompletionColumn(1);
    completer->setWidget(m_surnameLineEdit);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    m_surnameLineEdit->setCompleter(completer);

//    connect(completer, static_cast<void(QCompleter::*)(const QModelIndex &)>(&QCompleter::highlighted)),
//            [=](const QModelIndex &index) { });

    connect(completer, SIGNAL(highlighted(QModelIndex)),
            this, SLOT(surnameHighlighted(QModelIndex)));
}

//#include <QDebug>
void PersonWidget::surnameHighlighted(const QModelIndex &index)
{
//    qDebug() << "OK";
//    int col = index.column();
    int row = index.row();
//    qDebug() << completionModel->data(completionModel->index(row, 2)) << completionModel->data(completionModel->index(row, 3));

    m_nameLineEdit->setText(m_completionModel->data(m_completionModel->index(row, 2)).toString());
    m_middlenameLineEdit->setText(m_completionModel->data(m_completionModel->index(row, 3)).toString());
}
