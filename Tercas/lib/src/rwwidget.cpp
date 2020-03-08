#include <QtWidgets>
#include <QtSql>

#include "rwwidget.h"
#include "doublespinboxdelegate.h"

RWWidget::RWWidget(QWidget *parent)
    : QWidget(parent)
{
    m_tableView = new QTableView;
    m_tableView->setEnabled(false);

    QVBoxLayout *vbLayout = new QVBoxLayout;
    vbLayout->addWidget(m_tableView);

    m_editButton   = new QPushButton(trUtf8("Edit"));
    m_addButton    = new QPushButton(trUtf8("Add"));
    m_saveButton   = new QPushButton(trUtf8("Save"));
    m_saveButton->setEnabled(false);
    m_revertButton = new QPushButton(trUtf8("Revert"));
    m_revertButton->setEnabled(false);

    connect(m_editButton, SIGNAL(clicked(bool)),
            this, SLOT(onEditButtonClicked()));
    connect(m_addButton, SIGNAL(clicked(bool)),
            this, SLOT(onAddButtonClicked()));
    connect(m_saveButton, SIGNAL(clicked(bool)),
            this, SLOT(onSaveButtonClicked()));
    connect(m_revertButton, SIGNAL(clicked(bool)),
            this, SLOT(onRevertButtonClicked()));

    QVBoxLayout *vbCntlLayout = new QVBoxLayout;
    vbCntlLayout->addWidget(m_editButton);
    vbCntlLayout->addWidget(m_addButton);
    vbCntlLayout->addWidget(m_saveButton);
    vbCntlLayout->addWidget(m_revertButton);
    vbCntlLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(vbLayout);
    mainLayout->addLayout(vbCntlLayout);

    setLayout(mainLayout);
}

int RWWidget::adid() const
{
    return m_adid;
}

void RWWidget::setAdid(const int &adid)
{
    // Check here if adid is exist
    // ...

    m_adid = adid;

    m_model = new RWTableModel;
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QString filterString = QString("ad_pid=%1").arg(m_adid);
    m_model->setFilter(filterString);
    m_model->select();

    m_model->setHeaderData(1,  Qt::Horizontal, QString(trUtf8("Номер\nВПП")));
    m_model->setHeaderData(2,  Qt::Horizontal, QString(trUtf8("Длина")));
    m_model->setHeaderData(3,  Qt::Horizontal, QString(trUtf8("Ширина")));
    m_model->setHeaderData(4,  Qt::Horizontal, QString(trUtf8("Истинный\nкурс")));
    m_model->setHeaderData(5,  Qt::Horizontal, QString(trUtf8("Широта")));
    m_model->setHeaderData(6,  Qt::Horizontal, QString(trUtf8("Долгота")));
    m_model->setHeaderData(8,  Qt::Horizontal, QString(trUtf8("Покрытие")));
    m_model->setHeaderData(9,  Qt::Horizontal, QString(trUtf8("Освещение")));
    m_model->setHeaderData(10, Qt::Horizontal, QString(trUtf8("Круг\nполетов")));

    m_tableView->setModel(m_model);
    m_tableView->resizeColumnsToContents();
    m_tableView->hideColumn(0);
    m_tableView->hideColumn(7);
//    m_tableView->hideColumn(11);

    DoubleSpinBoxDelegate *doubleSpinBoxDelegate = new DoubleSpinBoxDelegate;
    m_tableView->setItemDelegateForColumn(5, doubleSpinBoxDelegate);
    m_tableView->setItemDelegateForColumn(6, doubleSpinBoxDelegate);
}

void RWWidget::onEditButtonClicked()
{
    m_editButton->setEnabled(false);
    m_addButton->setEnabled(false);
    m_saveButton->setEnabled(true);
    m_revertButton->setEnabled(true);
    m_tableView->setEnabled(true);

    m_model->m_adid = m_adid;
}

void RWWidget::onAddButtonClicked()
{
    m_editButton->setEnabled(false);
    m_addButton->setEnabled(false);
    m_saveButton->setEnabled(true);
    m_revertButton->setEnabled(true);
    m_tableView->setEnabled(true);

    m_model->m_adid = m_adid;
    m_model->insertRow(0);
    m_model->setData(m_model->index(0, 11), m_adid);
}

void RWWidget::onSaveButtonClicked()
{
    m_editButton->setEnabled(true);
    m_addButton->setEnabled(true);
    m_saveButton->setEnabled(false);
    m_revertButton->setEnabled(false);
    m_tableView->setEnabled(false);

    bool ret = m_model->submitAll();
    if (ret == false)
        qDebug() << "ERROR:" << m_model->lastError().text();
}

void RWWidget::onRevertButtonClicked()
{
    m_editButton->setEnabled(true);
    m_addButton->setEnabled(true);
    m_saveButton->setEnabled(false);
    m_revertButton->setEnabled(false);
    m_tableView->setEnabled(false);

    m_model->revertAll();
}

// RWTableModel implementation
//

RWTableModel::RWTableModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)
{
    setTable("rw.vw_rw");
}

QVariant RWTableModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    int col = idx.column();
    if (col == 5 || col == 6)
    {
        if (role == Qt::DisplayRole) {
            double ddd = QSqlTableModel::data(idx, role).toDouble();
            QString output = QString::number(ddd, 'f', 5);
            return output;
        }
    }
    else if (col == 11)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return m_adid;
        }
    }

    return QSqlTableModel::data(idx, role);
}

//bool RWTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    int col = index.column();
//    if (col == 11)
//    {
//        if (role == Qt::EditRole) {
//            qDebug() << "ID:" << m_adid;
//            return QSqlTableModel::setData(index, m_adid, Qt::EditRole);
//        }
//    }

//    return QSqlTableModel::setData(index, value, role);
//}
