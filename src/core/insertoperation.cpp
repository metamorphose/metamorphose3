#include "insertoperation.h"

void InsertOperation::operation(QString &name)
{
    QString parsedText = parseSubOps(textToInsert);

    switch (positionType) {
    case Prefix:
        name.prepend(parsedText);
        break;
    case Suffix:
        name.append(parsedText);
        break;
    case Fixed:
        if (atPosition < name.length()) {
            name.insert(atPosition, parsedText);
        }
        else {
            name.append(parsedText);
        }
        break;
    default:
        qCWarning(M3CORE) << "unhandled PositionType";
        break;
    }
}

void InsertOperation::setPositionType(const PositionTypes type)
{
    positionType = type;
}

void InsertOperation::setPosition(const int position)
{
    atPosition = position;
}

void InsertOperation::setTextToInsert(const QString text)
{
    textToInsert = text;
}
