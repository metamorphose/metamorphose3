#ifndef OPERATIONFORMITEM
#define OPERATIONFORMITEM

#include <QtCore>
#include <QtWidgets/QWidget>
#include "core/operationitem.h"

class OperationFormItem : public QWidget
{
    Q_OBJECT

public:
    explicit OperationFormItem(QWidget *parent = 0);
    virtual ~OperationFormItem() {}
    virtual OperationItem* getOperation() = 0;
    virtual void configureOperation() = 0;
};

#endif // OPERATIONFORMITEM
