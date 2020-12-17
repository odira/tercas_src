#include <QtWidgets>
#include <QtSql>

#include <QAbstractItemModel>

#include "NodePidArrayTableWidget.h"
#include "NodePidArrayTableModel.h"

NodePidArrayTableWidget::NodePidArrayTableWidget(QWidget *parent)
    : QWidget(parent),
      m_nodepidarr(QList<int>())
{
    m_model = new NodePidArrayTableModel(m_nodepidarr, this);

    m_view = new QTableView;
    m_view->setModel(m_model);
    m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->setShowGrid(true);
    m_view->setAlternatingRowColors(true);
    m_view->verticalHeader()->setVisible(true);
    m_view->setColumnWidth(0, 300);
    m_view->setColumnWidth(1, 300);
//    m_view->setFixedWidth(350);


    m_insertButton = new QPushButton(trUtf8("Insert node"));
    m_appendButton = new QPushButton(trUtf8("Append node"));
    m_removeButton = new QPushButton(trUtf8("Remove node"));

    connect(m_insertButton, SIGNAL(clicked(bool)),
            this, SLOT(insertButtonClicked()));
    connect(m_appendButton, SIGNAL(clicked(bool)),
            this, SLOT(appendButtonClicked()));
    connect(m_removeButton, SIGNAL(clicked(bool)),
            this, SLOT(removeButtonClicked()));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(m_insertButton);
    buttonLayout->addWidget(m_appendButton);
    buttonLayout->addWidget(m_removeButton);
    buttonLayout->addStretch(1);

//    QHBoxLayout *mainLayout = new QHBoxLayout;
//    mainLayout->addWidget(m_view);
//    mainLayout->addLayout(buttonLayout);
////    mainLayout->addStretch();

    QGridLayout *mainGrid = new QGridLayout;
    mainGrid->addWidget(m_view, 0, 0);
    mainGrid->addLayout(buttonLayout, 0, 1);
    mainGrid->setColumnMinimumWidth(0, 320);
    mainGrid->setColumnStretch(0, 1);

//    setLayout(mainLayout);
    setLayout(mainGrid);
}

void NodePidArrayTableWidget::setNodepidarr(const QString &nodepidarr)
{
    // Add here check for correct array string

    QList<int> l = fromString(nodepidarr);
    if (l != m_nodepidarr) {
        m_nodepidarr = l;
        m_model->setNodepidarr(m_nodepidarr);

        m_view->selectRow(0);

        emit nodepidarrChanged();
    }
}

QString NodePidArrayTableWidget::nodepidarr() const
{
    QString nodepidarr = toString(m_nodepidarr);
    return nodepidarr;
}

void NodePidArrayTableWidget::setEnabled(bool state)
{
    if (state == true) {
        m_appendButton->setEnabled(true);
        m_insertButton->setEnabled(true);
        m_removeButton->setEnabled(true);
    } else {
        m_appendButton->setEnabled(false);
        m_insertButton->setEnabled(false);
        m_removeButton->setEnabled(false);
    }
}

QList<int> NodePidArrayTableWidget::fromString(const QString &string)
{
    if (string.isEmpty())
        return QList<int>();

    if (string.left(1) != "{")
        return QList<int>();

    if (string.right(1) != "}")
        return QList<int>();

    QStringRef sref(&string, 1, string.length() - 2); // Remove braces
    QVector<QStringRef> v = sref.split(",");
    QList<int> list = QList<int>();
    for (const QStringRef &r: v) {
        list << r.toInt();
    }

    return list;
}

QString NodePidArrayTableWidget::toString(QList<int> arr) const
{
    if (arr.isEmpty())
        return QString();

    QString string;
    for (int i = 0; i < arr.size(); i++) {
        string += QString::number(arr.at(i));
        if (i < arr.size() - 1)
            string += ",";
    }
    string.prepend("{");
    string.append("}");

    return string;
}

void NodePidArrayTableWidget::insertButtonClicked()
{
    int maxval = -1;
    QSqlQuery query("SELECT MAX(pid) FROM data.vw_node");
    while (query.next()) {
        maxval = query.value(0).toInt();
    }

    if (maxval == -1)
        return;

    bool ok;
    QString offerstr = tr("Введите номер node (максимальное число %1)").arg(maxval);
    int val  = QInputDialog::getInt(this,
                                    tr("Введите число"),
                                    offerstr,
                                    -1, -1, maxval, 1,
                                    &ok);

    if (ok) {
        int row = m_view->currentIndex().row();
        if (row == -1) row = 0;
        m_model->insertRows(row, 1);
        m_model->setData(m_model->index(row, 1), val);

        m_nodepidarr = m_model->nodepidarr();
    }
}

void NodePidArrayTableWidget::appendButtonClicked()
{
    int maxval;
    QSqlQuery query("SELECT MAX(pid) FROM data.vw_node");
    while (query.next()) {
        maxval = query.value(0).toInt();
    }

    bool ok;
    QString offerstr = tr("Введите номер node (максимальное число %1)").arg(maxval);
    int val = QInputDialog::getInt(this,
                                   tr("Введите число"),
                                   offerstr,
                                   -1, -1, 100, 1,
                                   &ok);
    if (ok) {
        int row = m_nodepidarr.size();
        m_model->insertRows(row, 1);
        m_model->setData(m_model->index(row, 1), val);

        m_nodepidarr = m_model->nodepidarr();
    }
}

void NodePidArrayTableWidget::removeButtonClicked()
{
    QModelIndex indx = m_view->currentIndex();
    int row = indx.row();
    m_model->removeRows(row, 1);

    m_nodepidarr = m_model->nodepidarr();
}
