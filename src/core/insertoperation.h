#ifndef INSERTOPERATION_H
#define INSERTOPERATION_H

#include "operationitem.h"

class InsertOperation : public OperationItem
{
    Q_OBJECT

public:
    enum PositionType {
        Prefix = 0,
        Suffix = 1,
        Fixed = 2
    };
    Q_DECLARE_FLAGS(PositionTypes, PositionType)

    QString applyOperation(int opPosition, QString fileName) Q_DECL_OVERRIDE;
    void setPositionType(PositionTypes type);
    void setPosition(int position);
    void setTextToInsert(QString text);

private:
    PositionTypes positionType;
    int atPosition;
    QString textToInsert;
};

#endif // INSERTOPERATION_H
