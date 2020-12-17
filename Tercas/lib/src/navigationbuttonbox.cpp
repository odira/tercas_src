#include <QtWidgets>

#include "navigationbuttonbox.h"

VyborgNavigationButtonBox::VyborgNavigationButtonBox(QWidget *parent)
    : QHBoxLayout(parent), count_(0), currentIndex_(0), dirty_(false)
{
    firstButton    = new QPushButton;
    previousButton = new QPushButton;
    nextButton     = new QPushButton;
    lastButton     = new QPushButton;

    firstButton->setIcon(QIcon(":/arrow-first"));
    previousButton->setIcon(QIcon(":/arrow-left"));
    nextButton->setIcon(QIcon(":/arrow-right"));
    lastButton->setIcon(QIcon(":/arrow-last"));

    firstButton->setIconSize(QSize(48, 48));
    previousButton->setIconSize(QSize(48, 48));
    nextButton->setIconSize(QSize(48, 48));
    lastButton->setIconSize(QSize(48, 48));


    label = new QLabel;


    addWidget(firstButton);
    addWidget(previousButton);
    addWidget(label);
    addWidget(nextButton);
    addWidget(lastButton);


    connect(firstButton, SIGNAL(clicked()),
            this, SLOT(on_firstButtonClicked()));
    connect(previousButton, SIGNAL(clicked()),
            this, SLOT(on_previousButtonClicked()));
    connect(nextButton, SIGNAL(clicked()),
            this, SLOT(on_nextButtonClicked()));
    connect(lastButton, SIGNAL(clicked()),
            this, SLOT(on_lastButtonClicked()));

    update();
}

void VyborgNavigationButtonBox::setCurrentIndex(const int currentIndex)
{
    currentIndex_ = currentIndex;
    update();
}

int VyborgNavigationButtonBox::currentIndex() const
{
    return currentIndex_;
}

void VyborgNavigationButtonBox::setCount(const int count)
{
    count_ = count;
    update();
}

void VyborgNavigationButtonBox::on_firstButtonClicked()
{
    currentIndex_ = 0;
    emit goFirst();
    update();
}

void VyborgNavigationButtonBox::on_previousButtonClicked()
{
    if (currentIndex_ > 0)
        currentIndex_--;
    emit goPrevious();
    update();
}

void VyborgNavigationButtonBox::on_nextButtonClicked()
{
    if (currentIndex_ < count_ - 1)
        currentIndex_++;
    emit goNext();
    update();
}

void VyborgNavigationButtonBox::on_lastButtonClicked()
{
    currentIndex_ = count_ - 1;
    emit goLast();
    update();
}

void VyborgNavigationButtonBox::update()
{
    if (dirty_ == true) {
        firstButton->setEnabled(false);
        previousButton->setEnabled(false);
        nextButton->setEnabled(false);
        lastButton->setEnabled(false);
    } else {
        firstButton->setEnabled(true);
        previousButton->setEnabled(true);
        nextButton->setEnabled(true);
        lastButton->setEnabled(true);

        if (currentIndex_ == 0) {
            firstButton->setEnabled(false);
            previousButton->setEnabled(false);
        }
        else if (currentIndex_ == count_ - 1) {
            nextButton->setEnabled(false);
            lastButton->setEnabled(false);
        }

        QFont font("monospace");
        font.setFamily("courier");
        label->setFont(font);
        label->setText(tr("Item %1 of %2")
                       .arg(currentIndex_ + 1, 3, 10, QChar(' '))
                       .arg(count_));
    }
}

void VyborgNavigationButtonBox::setDirty(bool dirty)
{
    dirty_ = dirty;
    update();
}
