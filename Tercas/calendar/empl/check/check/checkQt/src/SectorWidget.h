#ifndef SECTORWIDGET_H
#define SECTORWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
QT_END_NAMESPACE


class SectorWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int pid READ pid WRITE setPid NOTIFY pidChanged USER true)

public:
    explicit SectorWidget(QWidget *parent = Q_NULLPTR);

    int pid() const;
    void setPid(const int &pid);

signals:
    void pidChanged(int);

private:
    int m_pid;

    QComboBox *m_labelCB;
};

#endif // SECTORWIDGET_H
