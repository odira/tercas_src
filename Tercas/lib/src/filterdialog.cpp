#include <QtWidgets>
#include <QtSql>
#include <QRegExp>

#include "filterdialog.h"

VyborgFilterDialog::VyborgFilterDialog(QWidget *parent)
    : QDialog(parent)
{
    caseSensitivityCheckBox = new QCheckBox(tr("Case sensitive filtering"));

    patternLineEdit = new QLineEdit;
    QLabel *patternLabel = new QLabel(tr("&Filter pattern"));
    patternLabel->setBuddy(patternLineEdit);

    syntaxComboBox = new QComboBox;
    syntaxComboBox->addItem(tr("Regular Expression"), QRegExp::RegExp);
    syntaxComboBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    syntaxComboBox->addItem(tr("Fixed String"), QRegExp::FixedString);
    QLabel *syntaxLabel = new QLabel(tr("Filter syntax"));
    syntaxLabel->setBuddy(syntaxComboBox);

    columnComboBox = new QComboBox;
    QLabel *columnLabel = new QLabel(tr("Filter column"));
    columnLabel->setBuddy(columnComboBox);

    filterButton = new QPushButton(tr("Filter"));
    filterButton->setEnabled(false);
    QPushButton *closeButton  = new QPushButton(tr("Close"));


    connect(patternLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(filterRegExpChanged()));
    connect(filterButton, SIGNAL(clicked()),
            SLOT(filter()));
    connect(closeButton, SIGNAL(clicked()),
            SLOT(close()));


    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(patternLabel, 0, 0);  gridLayout->addWidget(patternLineEdit, 0, 1);
    gridLayout->addWidget(columnLabel,  1, 0);  gridLayout->addWidget(columnComboBox,  1, 1);
    gridLayout->addWidget(syntaxLabel,  2, 0);  gridLayout->addWidget(syntaxComboBox,  2, 1);
    gridLayout->addWidget(caseSensitivityCheckBox, 3, 0, 1, 2);

    QGroupBox *groupBox = new QGroupBox(this);
    groupBox->setLayout(gridLayout);


    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(filterButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void VyborgFilterDialog::setModel(QSqlTableModel *model)
{
    m_model = model;
}

/**
 * Add column to search identified by table column number
 **/
void VyborgFilterDialog::addColumn(const QString &columnText, const int &columnData)
{
    QString fieldName = m_model->query().record().fieldName(columnData);
    columnComboBox->addItem(columnText, fieldName);
}

/**
 * Add column to search identified by table column name
 **/
void VyborgFilterDialog::addColumn(const QString &columnText, const QString &columnData)
{
    columnComboBox->addItem(columnText, columnData);
}

void VyborgFilterDialog::filterRegExpChanged()
{
    patternLineEdit->text().isEmpty() ?
            filterButton->setEnabled(false) :
            filterButton->setEnabled(true);
}

void VyborgFilterDialog::filter()
{
    QString columnData = columnComboBox->currentData().toString();

    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(
                syntaxComboBox->itemData(syntaxComboBox->currentIndex()).toInt());
    Qt::CaseSensitivity caseSensitivity =
            caseSensitivityCheckBox->isChecked() ? Qt::CaseSensitive
                                                 : Qt::CaseInsensitive;
    QString text = patternLineEdit->text();
    QRegExp regExp(text,
                   caseSensitivity,
                   syntax);

    QString filterExp;
    switch (syntax)
    {
    case QRegExp::Wildcard:
    default: {
        filterExp = columnData + " ILIKE \'%" + regExp.pattern() + "%\'";
        break;
    }
    }

//    QString filterExp = columnData + "=\'" + regExp.pattern() + "\'";
//    QString filterExp = columnData + " ILIKE \'%" + regExp.pattern() + "%\'";
//    QString filterExp = columnData + " REGEXP \'" + regExp.pattern() + "\'";
    qDebug() << "FILTER EXP:" << filterExp;

    m_model->setFilter(filterExp);

    done(QDialog::Accepted);
}

void VyborgFilterDialog::close()
{
    done(QDialog::Rejected);
}
