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
    OperationItem* getOperation() override;
    void configureOperation() override;
    QString name() override;

private slots:
    void positionSelection_buttonClicked(int id);
    void toInsert_selectionChanged();
    void toInsert_textChanged(const QString &arg1);

private:
    Ui::InsertForm *ui;
    InsertOperation *insertOperation;
};

#endif // INSERTFORM_H
