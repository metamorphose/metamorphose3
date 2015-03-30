#ifndef OPERATIONITEM_H
#define OPERATIONITEM_H

#include <QObject>

class OperationItem : public QObject
{
    Q_OBJECT

public:
    virtual QString applyOperation(int itemPosition,
                                   QString &fileName) = 0;
};

#endif // OPERATIONITEM_H
