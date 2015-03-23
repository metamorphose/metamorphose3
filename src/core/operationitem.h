#ifndef OPERATIONITEM_H
#define OPERATIONITEM_H
#include <QtCore>

class OperationItem
{
public:
    virtual ~OperationItem() {}
    virtual QString applyOperation(int opPosition) = 0;
};

#endif // OPERATIONITEM_H
