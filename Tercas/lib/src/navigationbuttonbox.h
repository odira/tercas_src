#ifndef VYBORGNAVIGATIONBUTTONBOX_H
#define VYBORGNAVIGATIONBUTTONBOX_H

#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class VyborgNavigationButtonBox : public QHBoxLayout
{
    Q_OBJECT

public:
    VyborgNavigationButtonBox(QWidget *parent = 0);

    void setDirty(bool dirty);
    int currentIndex() const;

signals:
    void goFirst();
    void goPrevious();
    void goNext();
    void goLast();

public slots:
    void setCount(const int count);
    void setCurrentIndex(const int currentIndex);
    
private slots:
    void on_firstButtonClicked();
    void on_previousButtonClicked();
    void on_nextButtonClicked();
    void on_lastButtonClicked();

private:
    void update();

private:
    QPushButton *firstButton;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *lastButton;
    QLabel *label;

    int count_;
    int currentIndex_;
    int dirty_;
};

#endif // VYBORGNAVIGATIONBUTTONBOX_H
