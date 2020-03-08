#ifndef SECTORPIDARRAYWIDGET_H
#define SECTORPIDARRAYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class PlainSectorsListWidget;

class SectorPidArrayWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString array READ array WRITE setArray NOTIFY arrayChanged USER true)

public:
    explicit SectorPidArrayWidget(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

    void setArray(const QString &array);
    QString array() const;

signals:
    void arrayChanged(QString array);

private slots:
    QList<int> stringToArray(const QString &arrayStr);
    QString arrayToString(QList<int> array) const;

    void showPlainSectorsListW();
    void addSectorPid(int pid);

private:
    QList<int> m_sectorPidArr;

private:
    QLineEdit *m_sectorPidArrLE;
    QPushButton *m_plusButton;
    QPushButton *m_minusButton;
    PlainSectorsListWidget *m_plainSectorsListW;
};


QT_BEGIN_NAMESPACE
class QComboBox;
QT_END_NAMESPACE

class PlainSectorsListWidget : public QWidget
{
    Q_OBJECT

public:
    PlainSectorsListWidget(QWidget *parent = Q_NULLPTR);

signals:
    void addSectorSignal(int pid);

private slots:
    void sectorActivated(int row);

private:
    QComboBox *m_comboBox;
};

#endif // SECTORPIDARRAYWIDGET_H
