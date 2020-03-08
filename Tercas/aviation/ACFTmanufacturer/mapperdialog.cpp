#include <QtWidgets>
#include <QtSql>

#include "declarations.h"
#include "mapperdialog.h"

MapperDialog::MapperDialog(QSortFilterProxyModel *proxy, QWidget *parent)
    : VyborgMapperDialog(proxy, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
    commonNameLineEdit = new QLineEdit;
    nameLineEdit = new QLineEdit;
    countryIdLineEdit = new QLineEdit;

    mapper_->addMapping(commonNameLineEdit, ACFTmanufacturer_commonName);
    mapper_->addMapping(nameLineEdit,       ACFTmanufacturer_name);
    mapper_->addMapping(countryIdLineEdit,  ACFTmanufacturer_country_id);
}

void MapperDialog::layoutPrivateWidgets()
{
    QHBoxLayout *subLayout1 = new QHBoxLayout;
    subLayout1->addWidget(commonNameLineEdit);
    subLayout1->addStretch();

    QHBoxLayout *subLayout2 = new QHBoxLayout;
    subLayout2->addWidget(nameLineEdit);
    subLayout2->addStretch();

    QHBoxLayout *subLayout3 = new QHBoxLayout;
    subLayout3->addWidget(countryIdLineEdit);
    subLayout3->addStretch();


    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(trUtf8("Common Name"), subLayout1);
    formLayout->addRow(trUtf8("Name"),        subLayout2);
    formLayout->addRow(trUtf8("Country"),     subLayout3);


    privateWidgetsLayout->addLayout(formLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (dirty_ == true) {

    } else {

    }
}
