#include <QtWidgets>
#include <QtSql>

#include "chartsdialog.h"

VyborgChartsDialog::VyborgChartsDialog(QSqlTableModel *model, QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    m_model = model;

    QPushButton *closeButton = new QPushButton(trUtf8("Close"));
    connect(closeButton, SIGNAL(clicked(bool)),
            this, SLOT(close()));

    QDialogButtonBox *bbox = new QDialogButtonBox;
    bbox->setOrientation(Qt::Vertical);
    bbox->addButton(closeButton, QDialogButtonBox::ActionRole);

    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(bbox);
    buttonsLayout->addStretch();

    m_chartsLayout = new QVBoxLayout;


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(m_chartsLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);


    QSize parentSize = this->parentWidget()->size();
    resize(parentSize.width() - 50, parentSize.height() - 50);
    move(25, 25);

    setModal(true);
    setSizeGripEnabled(false);
//    setSizePolicy(QSizePolicy::Fixed);

    setWindowTitle(trUtf8("Charts Dialog"));
}

QVBoxLayout * VyborgChartsDialog::layout() const
{
    return m_chartsLayout;
}
