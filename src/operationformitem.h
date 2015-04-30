#ifndef OPERATIONFORMITEM_H
#define OPERATIONFORMITEM_H

#include <QtWidgets/QWidget>
#include "core/operationitem.h"
#include "suboperationsform.h"

Q_DECLARE_LOGGING_CATEGORY(M3GUI)

namespace Ui {
class OperationFormItem;
}

class OperationFormItem : public QWidget
{
    Q_OBJECT

public:
    explicit OperationFormItem(QWidget *parent = 0);
    ~OperationFormItem();
    virtual OperationItem* getOperation() = 0;
    virtual void configureOperation() = 0;
    virtual QString name() = 0;
    bool applyToName = true;
    bool applyToExtension = false;

protected:
    SubOperationsForm *subOperationsForm;
    Ui::OperationFormItem *formItemUi;
};

#endif // OPERATIONFORMITEM_H
