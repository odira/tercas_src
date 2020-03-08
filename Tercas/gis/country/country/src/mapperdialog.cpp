#include <QtWidgets>
#include <QtSql>

#include "mapperdialog.h"
#include "declarations.h"

MapperDialog::MapperDialog(QSqlTableModel *model, QWidget *parent)
    : VyborgMapperDialog(model, parent)
{
    createPrivateWidgets();
    layoutPrivateWidgets();
    updatePrivateWidgets();
}

void MapperDialog::createPrivateWidgets()
{
    m_nameLE         = new QLineEdit;
    m_nameruLE       = new QLineEdit;
    m_nameshortLE    = new QLineEdit;
    m_nameshortruLE  = new QLineEdit;
    m_iso3166code2LE = new QLineEdit;
    m_iso3166code3LE = new QLineEdit;
    m_iso3166codenLE = new QLineEdit;
    m_noteLE         = new QLineEdit;
    m_noteruLE       = new QLineEdit;

    QDataWidgetMapper* m_mapper = mapper();
    m_mapper->addMapping(m_nameLE,         country_name);
    m_mapper->addMapping(m_nameruLE,       country_nameru);
    m_mapper->addMapping(m_nameshortLE,    country_nameshort);
    m_mapper->addMapping(m_nameshortruLE,  country_nameshortru);
    m_mapper->addMapping(m_iso3166code2LE, country_iso3166code2);
    m_mapper->addMapping(m_iso3166code3LE, country_iso3166code3);
    m_mapper->addMapping(m_iso3166codenLE, country_iso3166coden);
    m_mapper->addMapping(m_noteLE,         country_note);
    m_mapper->addMapping(m_noteruLE,       country_noteru);
}

void MapperDialog::layoutPrivateWidgets()
{
    // Основные данные

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(trUtf8("Name"), m_nameLE);
    formLayout->addRow(trUtf8("Название"), m_nameruLE);
    formLayout->addRow(trUtf8("Short name"), m_nameshortLE);
    formLayout->addRow(trUtf8("Сокращенное название"), m_nameshortruLE);
    formLayout->addRow(trUtf8("ISO3166 code 2"), m_iso3166code2LE);
    formLayout->addRow(trUtf8("ISO3166 code 3"), m_iso3166code3LE);
    formLayout->addRow(trUtf8("ISO3166 Number"), m_iso3166codenLE);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);

    QVBoxLayout *privateWidgetsLayout = layout();
    privateWidgetsLayout->addLayout(mainLayout);
}

void MapperDialog::updatePrivateWidgets()
{
    if (isDirty())
    {
        m_nameLE->setEnabled(false);
        m_nameruLE->setEnabled(false);
        m_nameshortLE->setEnabled(false);
        m_nameshortruLE->setEnabled(false);
        m_iso3166code2LE->setEnabled(false);
        m_iso3166code3LE->setEnabled(false);
        m_iso3166codenLE->setEnabled(false);
        m_noteLE->setEnabled(false);
        m_noteruLE->setEnabled(false);
    }
    else
    {
        m_nameLE->setEnabled(true);
        m_nameruLE->setEnabled(true);
        m_nameshortLE->setEnabled(true);
        m_nameshortruLE->setEnabled(true);
        m_iso3166code2LE->setEnabled(true);
        m_iso3166code3LE->setEnabled(true);
        m_iso3166codenLE->setEnabled(true);
        m_noteLE->setEnabled(true);
        m_noteruLE->setEnabled(true);
    }
}
