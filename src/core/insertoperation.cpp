#include "insertoperation.h"

void InsertOperation::operation(int itemPosition, QString &name)
{
    parseSubOps(itemPosition, textToInsert);

    switch (positionType) {
    case Prefix:
        name.prepend(textToInsert);
        break;
    case Suffix:
        name.append(textToInsert);
        break;
    case Fixed:
        if (atPosition < name.length()) {
            name.insert(atPosition, textToInsert);
        }
        else {
            name.append(textToInsert);
        }
        break;
    default:
        qCWarning(M3CORE) << "unhandled PositionType";
        break;
    }
}

void InsertOperation::setPositionType(PositionTypes type)
{
    positionType = type;
}

void InsertOperation::setPosition(int position)
{
    atPosition = position;
}

void InsertOperation::setTextToInsert(QString text)
{
    textToInsert = text;
}
