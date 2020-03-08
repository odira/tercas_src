#include <QtWidgets>
//#include <QTableWidget>
#include <QtSql>

#include "orgdialog.h"


OrgDialog::OrgDialog(QWidget *parent) :
    QDialog(parent)
{
    QSqlDatabase::database().transaction();
    QSqlQuery query("SELECT orgRu FROM org");
    QSqlDatabase::database().commit();

    m_tableWidget = new QTableWidget(query.size(), 1, this);
    QStringList horHeaders;
    horHeaders << "Список организаций";
    m_tableWidget->setHorizontalHeaderLabels(horHeaders);
    m_tableWidget->verticalHeader()->setVisible(false);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableWidget->setShowGrid(true);
    m_tableWidget->setStyleSheet("QTableView {selection-background-color: yellow;}");
    connect(m_tableWidget, SIGNAL(cellClicked(int,int)),
            SLOT(on_tableWidgetCellClicked(int,int)));

    int i = 0;
    while (query.next()) {
        QTableWidgetItem *item = new QTableWidgetItem(query.value(0).toString());
        m_tableWidget->setItem(i, 0, item);
        i++;
    }


    m_acceptButton = new QPushButton(trUtf8("Accept"));
    m_acceptButton->setEnabled(false);
    connect(m_acceptButton, SIGNAL(clicked()),
            SLOT(on_acceptButtonClicked()));

    QPushButton *closeButton = new QPushButton(trUtf8("Close"));
    connect(closeButton, SIGNAL(clicked()),
            SLOT(reject()));

    QHBoxLayout *buttonBox = new QHBoxLayout;
    buttonBox->addWidget(m_acceptButton);
    buttonBox->addWidget(closeButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_tableWidget);
    mainLayout->addLayout(buttonBox);

    setLayout(mainLayout);


    setModal(true);
    resize(parent->width() * 9/10, parent->height() * 9/10);
}

void OrgDialog::on_tableWidgetCellClicked(int row, int column)
{
    QTableWidgetItem *item = m_tableWidget->item(row, column);
    QString org = item->text();
    setRetValue(org);

    m_acceptButton->setEnabled(true);
}

void OrgDialog::setRetValue(const QString &retValue)
{
    if (retValue != m_retValue) {
        m_retValue = retValue;
    }
}

QString OrgDialog::retValue() const
{
    return m_retValue;
}

void OrgDialog::on_acceptButtonClicked()
{
    done(QDialog::Accepted);
}
