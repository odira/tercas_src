#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSpinBox;
class QLineEdit;
class QRadioButton;
class QPlainTextEdit;
QT_END_NAMESPACE

class NodeWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int nodepid READ nodepid WRITE setNodepid NOTIFY nodepidChanged USER true)

public:
    NodeWidget(QWidget *parent = Q_NULLPTR);

    void setNodepid(const int &nodepid = -1);
    int nodepid();

public slots:
    void setEnabled(bool state);

signals:
    void nodepidChanged(int);

private slots:
//    void coordEdited(const QString &text);
    void update();

private:
    // visual
//    QLineEdit *m_nodepidLE;
    QSpinBox *m_nodepidSB;
    QLineEdit *m_latLineEdit;
    QLineEdit *m_lonLineEdit;
    QLineEdit *m_sridLineEdit;
    QRadioButton *m_radioButton1;
    QRadioButton *m_radioButton2;
    QPlainTextEdit *m_nodenoteruPTE;

    // non-visual
    int m_nodepid;
};
