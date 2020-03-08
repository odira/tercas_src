#ifndef MAPPERDIALOG_H
#define MAPPERDIALOG_H

#include <vyborg.h>

class QLineEdit;


class MapperDialog : public VyborgMapperDialog
{
    Q_OBJECT


public:
    MapperDialog(QSortFilterProxyModel *proxy, QWidget *parent = 0);

protected:
    virtual void createPrivateWidgets();
    virtual void layoutPrivateWidgets();
    virtual void updatePrivateWidgets();

private:
    QLineEdit *commonNameLineEdit;
    QLineEdit *nameLineEdit;
    QLineEdit *countryIdLineEdit;
};

#endif // MAPPERDIALOG_H
