#ifndef NODEPIDARRAYTABLEWIDGET_H
#define NODEPIDARRAYTABLEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTableView;
class QPushButton;
QT_END_NAMESPACE

class NodePidArrayTableModel;

class NodePidArrayTableWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString nodepidarr READ nodepidarr WRITE setNodepidarr NOTIFY nodepidarrChanged USER true)

public:
    explicit NodePidArrayTableWidget(QWidget *parent = 0);

    void setNodepidarr(const QString &nodepidarr);
    QString nodepidarr() const;

    void setEnabled(bool state);

signals:
    void nodepidarrChanged();

private slots:
    void insertButtonClicked();
    void appendButtonClicked();
    void removeButtonClicked();

private:
    QList<int> fromString(const QString &string);
    QString toString(QList<int> arr) const;

    QList<int> m_nodepidarr;
    NodePidArrayTableModel *m_model;

    QTableView  *m_view;
    QPushButton *m_insertButton;
    QPushButton *m_appendButton;
    QPushButton *m_removeButton;
};

#endif // NODEPIDARRAYTABLEWIDGET_H
