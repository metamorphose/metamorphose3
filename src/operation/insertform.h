#ifndef INSERTFORM_H
#define INSERTFORM_H

#include "operationformitem.h"
#include "core/insertoperation.h"

namespace Ui {
class InsertForm;
}

class InsertForm : public OperationFormItem
{
    Q_OBJECT

public:
    explicit InsertForm(QWidget *parent = 0);
    ~InsertForm();
    OperationItem* getOperation() Q_DECL_OVERRIDE;
    void configureOperation() Q_DECL_OVERRIDE;

private slots:
    void on_positionSelection_buttonClicked(int id);

private:
    Ui::InsertForm *ui;
    InsertOperation *insertOperation;
};

#endif // INSERTFORM_H
