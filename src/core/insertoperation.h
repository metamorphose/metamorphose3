#ifndef INSERTOPERATION_H
#define INSERTOPERATION_H

#include <QtCore/QObject>
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
    void setPositionType(const InsertOperation::PositionTypes type);
    void setPosition(const int position);
    void setTextToInsert(const QString text);

protected:
    void operation(QString &name) override;

private:
    PositionTypes positionType;
    int atPosition;
    QString textToInsert;
};

#endif // INSERTOPERATION_H
