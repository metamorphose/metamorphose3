#ifndef INSERTOPERATION_H
#define INSERTOPERATION_H

#include "operationitem.h"

class InsertOperation : public OperationItem
{
public:
    enum PositionType {
        Prefix = 0,
        Suffix = 1,
        Fixed = 2
    };

    explicit InsertOperation();
    ~InsertOperation();

    QString applyOperation(int opPosition) Q_DECL_OVERRIDE;

protected:
    PositionType positionType;
    int position;
    QString text;
};

#endif // INSERTOPERATION_H
