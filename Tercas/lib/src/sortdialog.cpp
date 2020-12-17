#include <QtWidgets>
#include <QtSql>

#include "sortdialog.h"

#include <QDebug>

//VyborgSortDialog::VyborgSortDialog(QSortFilterProxyModel *proxy, QWidget *parent)
VyborgSortDialog::VyborgSortDialog(QSqlTableModel *model, QWidget *parent)
    : QDialog(parent),
      m_model(model)
{
//    proxy_ = proxy;

    columnComboBox = new QComboBox;
    QLabel *columnLabel = new QLabel(tr("Sort column"));
    columnLabel->setBuddy(columnComboBox);

    orderComboBox = new QComboBox;
    orderComboBox->addItem(tr("Ascending"), Qt::AscendingOrder);
    orderComboBox->addItem(tr("Descending"), Qt::DescendingOrder);
    QLabel *orderLabel = new QLabel(tr("Ascend/Descend order"));
    orderLabel->setBuddy(orderComboBox);

    caseSensitivityCheckBox = new QCheckBox(tr("Case sensitive sorting"));

    QPushButton *sortButton = new QPushButton(tr("Sort"));
    QPushButton *closeButton  = new QPushButton(tr("Close"));

    connect(sortButton, SIGNAL(clicked()),
            SLOT(sort()));
    connect(closeButton, SIGNAL(clicked()),
            SLOT(close()));

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(columnLabel,  0, 0);  gridLayout->addWidget(columnComboBox,  0, 1);
    gridLayout->addWidget(orderLabel,   1, 0);  gridLayout->addWidget(orderComboBox,   1, 1);
    gridLayout->addWidget(caseSensitivityCheckBox, 2, 0, 1, 2);

    QGroupBox *groupBox = new QGroupBox(this);
    groupBox->setLayout(gridLayout);


    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(sortButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void VyborgSortDialog::setModel(QSqlTableModel *model)
{
    m_model = model;
}

void VyborgSortDialog::addColumn(const QString &columnText, const int columnData)
{
    columnComboBox->addItem(columnText, columnData);
}

void VyborgSortDialog::sort()
{
    int col = columnComboBox->currentData().toInt();
    Qt::SortOrder order = Qt::SortOrder(orderComboBox->currentData().toInt());
    Qt::CaseSensitivity cs = caseSensitivityCheckBox->isChecked() ? Qt::CaseSensitive :
                                                                    Qt::CaseInsensitive;

//    proxy_->setSortCaseSensitivity(cs);
//    proxy_->sort(col, order);
//    QString sortStr = " ORDER BY ";
//    QString query = QSqlQueryModel::query()
//    qDebug() << "Col: " << col;

//    m_model->sort(1, Qt::AscendingOrder);
//    m_model->setSort(col, order);
//    m_model->setSort(1, Qt::AscendingOrder);

//    m_model->select();

    m_model->setSort(col, order);
    done(QDialog::Accepted);
}

void VyborgSortDialog::close()
{
    done(QDialog::Rejected);
}
