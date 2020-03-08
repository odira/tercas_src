#include <QtWidgets>

#include "mappercontrolbuttonbox.h"

VyborgMapperControlButtonBox::VyborgMapperControlButtonBox(QWidget *parent)
    : QDialogButtonBox(parent),
      m_dirty(false)
{
    m_editButton   = new QPushButton(tr("Edit"));
    m_submitButton = new QPushButton(tr("Submit"));
    m_revertButton = new QPushButton(tr("Revert"));
    m_closeButton  = new QPushButton(tr("Close"));

    addButton(m_editButton,   QDialogButtonBox::ActionRole);
    addButton(m_submitButton, QDialogButtonBox::ActionRole);
    addButton(m_revertButton, QDialogButtonBox::ActionRole);
    addButton(m_closeButton,  QDialogButtonBox::ActionRole);

    connect(m_editButton, SIGNAL(clicked()),
            this, SLOT(on_editButtonClicked()));
    connect(m_submitButton, SIGNAL(clicked()),
            this, SLOT(on_submitButtonClicked()));
    connect(m_revertButton, SIGNAL(clicked()),
            this, SLOT(on_revertButtonClicked()));
    connect(m_closeButton, SIGNAL(clicked()),
            this, SLOT(on_closeButtonClicked()));

    setDirty(m_dirty);
}

void VyborgMapperControlButtonBox::on_editButtonClicked()
{
    setDirty(true);
    emit edit();
}

void VyborgMapperControlButtonBox::on_submitButtonClicked()
{
    setDirty(false);
    emit submit();
}

void VyborgMapperControlButtonBox::on_revertButtonClicked()
{
    setDirty(false);
    emit revert();
}

void VyborgMapperControlButtonBox::on_closeButtonClicked()
{
    emit close();
}

void VyborgMapperControlButtonBox::setDirty(bool dirty)
{
    m_dirty = dirty;

    if (m_dirty) {
        m_editButton->setEnabled(false);
        m_submitButton->setEnabled(true);
        m_revertButton->setEnabled(true);
        m_closeButton->setEnabled(true);
    } else {
        m_editButton->setEnabled(true);
        m_submitButton->setEnabled(false);
        m_revertButton->setEnabled(false);
        m_closeButton->setEnabled(true);
    }
}
