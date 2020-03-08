#ifndef COORDWIDGET_H
#define COORDWIDGET_H


#include <QWidget>


QT_BEGIN_NAMESPACE
class QLineEdit;
class QPlainTextEdit;
class QListView;
//class QSqlQueryModel;
QT_END_NAMESPACE


class CoordWidget : public QWidget
{
    Q_OBJECT
//    Q_PROPERTY(int pid READ pid WRITE setPid NOTIFY pidChanged USER true)

public:
    CoordWidget(QWidget *parent = Q_NULLPTR);

    void setPid(int const &pid);
    int pid() const;

    QLineEdit * getLatLE() { return m_latgggLE; }
    QLineEdit * getLonLE() { return m_longggLE; }
    QLineEdit * getSridLE() { return m_sridLE; }

signals:
    void pidChanged(int m_pid);

private slots:
    void fieldEdited(const QString &);

private:
    QLineEdit *m_latggLE;
    QLineEdit *m_latmmLE;
    QLineEdit *m_latssLE;
    QLineEdit *m_longgLE;
    QLineEdit *m_lonmmLE;
    QLineEdit *m_lonssLE;
    QLineEdit *m_latgggLE;
    QLineEdit *m_longggLE;
    QLineEdit *m_sridLE;
    QListView *m_listView;

//    QSqlQueryModel *m_completionModel;
    int m_pid;
    qreal m_lat;
    qreal m_lon;
    qint8 m_latgg;
    qint8 m_latmm;
    qreal m_latss;
    qint8 m_longg;
    qint8 m_lonmm;
    qreal m_lonss;
    qint16 m_srid;
    QString m_geog;
};


#endif // COORDWIDGET_H
