#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <vyborg.h>

class MainDialog : public VyborgMainDialog
{
    Q_OBJECT

 public:
    MainDialog(QWidget *parent = 0);

protected:
    virtual void setupModel() Q_DECL_OVERRIDE;
    virtual void setupView() Q_DECL_OVERRIDE;
    virtual void setupMapperDialog() Q_DECL_OVERRIDE;
    virtual void setupFilterDialog() Q_DECL_OVERRIDE;
    virtual void setupSortDialog() Q_DECL_OVERRIDE;
};

#endif // MAINDIALOG_H
