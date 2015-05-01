#include "operationformitem.h"
#include "ui_operationformitem.h"

OperationFormItem::OperationFormItem(QWidget *parent) :
    QWidget(parent),
    formItemUi(new Ui::OperationFormItem)
{
    qCDebug(M3GUI) << "init OperationFormItem";
    formItemUi->setupUi(this);
}

void OperationFormItem::initSubOperations(QLineEdit *mainInput)
{
    subOperationsForm = new SubOperationsForm(formItemUi->subOperation);
    connect(subOperationsForm, SIGNAL(subOperationAdded(QString)),
            this, SLOT(insertSubOpText(QString)));
    this->mainInput = mainInput;
}

OperationFormItem::~OperationFormItem()
{
    delete formItemUi;
}

void OperationFormItem::insertSubOpText(QString text)
{
    if (mainInput && mainInput->isEnabled()) {
        mainInput->insert(text);
        mainInput->setFocus();
        return;
    }
    qCWarning(M3GUI, "Can't insert sub-operation text");
}
