#include "operationitem.h"

void OperationItem::applyOperation(int itemPosition, std::pair<QString, QString> &name)
{
    if (applyToName) {
        operation(name.first);
    }
    if (applyToExtension) {
        operation(name.second);
    }
}

void OperationItem::setApplyToName(bool apply)
{
    applyToName = apply;
}

void OperationItem::setApplyToExtension(bool apply)
{
    applyToExtension = apply;
}
