#ifndef NODEWIDGET_H
#define NODEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPlainTextEdit;
QT_END_NAMESPACE

class NodeWidget : public QWidget
{
    Q_OBJECT

public:
    NodeWidget(QWidget *parent = 0);

    QLineEdit* latggLE() { return m_latggLineEdit; }
    QLineEdit* latmmLE() { return m_latmmLineEdit; }
    QLineEdit* latssLE() { return m_latssLineEdit; }
    QLineEdit* longgLE() { return m_longgLineEdit; }
    QLineEdit* lonmmLE() { return m_lonmmLineEdit; }
    QLineEdit* lonssLE() { return m_lonssLineEdit; }
    QLineEdit* sridLE() { return m_sridLineEdit; }
    QPlainTextEdit* notePTE() { return m_noteruPTE; }

private:
    QLineEdit *m_latggLineEdit;
    QLineEdit *m_latmmLineEdit;
    QLineEdit *m_latssLineEdit;
    QLineEdit *m_longgLineEdit;
    QLineEdit *m_lonmmLineEdit;
    QLineEdit *m_lonssLineEdit;
    QLineEdit *m_sridLineEdit;
    QPlainTextEdit *m_noteruPTE;

    qint8 m_latgg;
    qint8 m_latmm;
    qreal m_latss;
    qint8 m_longg;
    qint8 m_lonmm;
    qreal m_lonss;
    qint16 m_srid;
    QString m_noteru;
};

#endif // NODEWIDGET_H
