#include <QtWidgets>
#include <QtSql>

#include "mapperdialog.h"
#include "mappercontrolbuttonbox.h"
#include "navigationbuttonbox.h"

VyborgMapperDialog::VyborgMapperDialog(QSqlTableModel *model, QWidget *parent)
    : QDialog(parent),
      m_state(Normal)
{
    m_model = model;

    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);


    m_controlButtonBox = new VyborgMapperControlButtonBox;
    m_controlButtonBox->setOrientation(Qt::Vertical);

    connect(m_controlButtonBox, SIGNAL(edit()),
            SLOT(edit()));
    connect(m_controlButtonBox, SIGNAL(submit()),
            SLOT(submit()));
    connect(m_controlButtonBox, SIGNAL(revert()),
            SLOT(revert()));
    connect(m_controlButtonBox, SIGNAL(close()),
            SLOT(close()));


    m_navButtonBox = new VyborgNavigationButtonBox;

    connect(m_navButtonBox, SIGNAL(goFirst()),
            m_mapper, SLOT(toFirst()));
    connect(m_navButtonBox, SIGNAL(goPrevious()),
            m_mapper, SLOT(toPrevious()));
    connect(m_navButtonBox, SIGNAL(goNext()),
            m_mapper, SLOT(toNext()));
    connect(m_navButtonBox, SIGNAL(goLast()),
            m_mapper, SLOT(toLast()));


    m_privateWidgetsLayout = new QVBoxLayout;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(m_navButtonBox);
    vLayout->addLayout(m_privateWidgetsLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(vLayout);
    mainLayout->addWidget(m_controlButtonBox);

    setLayout(mainLayout);

//    connect(m_mapper, SIGNAL(currentIndexChanged(int)),
//            this, SLOT(setCurrentRow(int)));
//    connect(m_mapper, SIGNAL())

    setState(Normal);
//    setAttribute(Qt::WA_DeleteOnClose);
}

void VyborgMapperDialog::updateControlWidgets()
{
    switch (m_state)
    {
    case Normal:

        m_controlButtonBox->setDirty(false);
        m_navButtonBox->setDirty(false);

        break;

    case Edit:
    case Add:

        m_controlButtonBox->setDirty(true);
        m_navButtonBox->setDirty(true);

        break;

    default:
        break;
    }

    m_navButtonBox->setCount(m_model->rowCount());
    m_navButtonBox->setCurrentIndex(m_mapper->currentIndex());
}

void VyborgMapperDialog::edit()
{
    setState(Edit);
}

#include <QDebug>
void VyborgMapperDialog::submit()
{
    if (m_mapper->submit() == true) {
        m_model->database().transaction();
        if (m_model->submitAll()) {
            bool ret = m_model->database().commit();
        } else {
            m_model->revertAll();
            m_model->database().rollback();
            QMessageBox::warning(this,
                                 tr("Commit Changes to Model"),
                                 tr("The database reported an error:\n%1").arg(m_model->lastError().text()));
        }
    } else {
        QMessageBox::warning(this,
                             tr("Submit to mapper"),
                             tr("The mapper reported an error: %!").arg(m_model->lastError().text()));
    }

//    qDebug() << "OK";
//    if (!m_mapper->submit())
//        qDebug() << m_model->lastError().text();
//    qDebug() << "OK1\n";

//    m_model->database().transaction();
//    m_model->submitAll();
//    m_model->database().commit();

//    qDebug() << "OK";
//    if (!m_model->submitAll())
//        qDebug() << m_model->lastError().text();


    if (m_state == Add)
    {
        setState(Normal);
        close();
    }
    else if (m_state == Edit)
    {
        setState(Normal);
    }
}

void VyborgMapperDialog::revert()
{
    int curRow = m_mapper->currentIndex();

    m_mapper->revert();
    m_model->revert();

    m_mapper->setCurrentIndex(qMin(curRow, m_model->rowCount()));

    setState(Normal);
}

void VyborgMapperDialog::close()
{
    if (m_state == Edit && m_model->isDirty())
    {
        int ret = QMessageBox::warning(this,
                                 tr("WARNING"),
                                 tr("Unsaved data exists!\nDo you want to save data?"),
                                 QMessageBox::Save | QMessageBox::Discard);
        if (ret == QMessageBox::Save)
            submit();
        else if (ret == QMessageBox::Discard)
            revert();

        done(QDialog::Rejected);
    }
    else
        done(QDialog::Accepted);
}

void VyborgMapperDialog::setCurrentRow(int row)
{
    m_mapper->setCurrentIndex(row);

    updateControlWidgets();
//    m_navButtonBox->setCurrentIndex(row);
}

QDataWidgetMapper* VyborgMapperDialog::mapper()
{
    return m_mapper;
}

QVBoxLayout* VyborgMapperDialog::layout()
{
    return m_privateWidgetsLayout;
}

void VyborgMapperDialog::setState(State state)
{
    if (state != m_state)
    {
        m_state = state;

        updateControlWidgets();
        updatePrivateWidgets();
    }
}

VyborgMapperDialog::State VyborgMapperDialog::state() const
{
    return m_state;
}
