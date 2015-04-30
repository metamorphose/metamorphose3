#include "operationformitem.h"
#include "ui_operationformitem.h"


OperationFormItem::OperationFormItem(QWidget *parent) :
    QWidget(parent),
    formItemUi(new Ui::OperationFormItem)
{
    qCDebug(M3GUI) << "init OperationFormItem";
    formItemUi->setupUi(this);

    subOperationsForm = new SubOperationsForm(formItemUi->subOperation);
}

OperationFormItem::~OperationFormItem()
{
    delete formItemUi;
}
