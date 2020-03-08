#include <QtWidgets>
#include <QtSql>

#include "SectorWidget.h"


SectorWidget::SectorWidget(QWidget *parent)
    : QWidget(parent),
      m_pid(-1)
{
    QString queryString = QString("SELECT * FROM public.dblink('dbname=gis', 'SELECT pid, label FROM fir.vw_sector') AS ct(pid INTEGER, label TEXT)");
    QSqlQuery query(queryString);
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(queryString);

    m_labelCB = new QComboBox;
    m_labelCB->setModel(model);
    m_labelCB->setModelColumn(1);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(2);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_labelCB);

    setLayout(mainLayout);
}

void SectorWidget::setPid(const int &pid)
{
    if (pid != m_pid)
    {
        m_pid = pid;
        emit pidChanged(m_pid);

        QString queryString = QString("SELECT label FROM public.dblink('dbname=gis', 'SELECT label FROM fir.vw_sector WHERE pid=%1') AS ct(label TEXT)")
                .arg(m_pid);
        QSqlQuery query(queryString);
        while (query.next()) {
            QString label = query.value(0).toString();
            m_labelCB->setCurrentText(label);
            break;
        }
        query.clear();
    }
}

int SectorWidget::pid() const
{
    QModelIndex indx = m_labelCB->model()->index(m_labelCB->currentIndex(), 0);
    int pid = m_labelCB->model()->data(indx).toInt();
    return pid;
}
