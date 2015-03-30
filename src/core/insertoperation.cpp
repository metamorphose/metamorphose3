#include <QtCore/QtDebug>
#include "insertoperation.h"

QString InsertOperation::applyOperation(int itemPosition, QString &fileName)
{
    switch (positionType) {
    case Prefix:
        fileName.prepend(textToInsert);
        break;
    case Suffix:
        fileName.append(textToInsert);
        break;
    case Fixed:
        if (atPosition < fileName.length()) {
            fileName.insert(atPosition, textToInsert);
        }
        else {
            fileName.append(textToInsert);
        }
        break;
    default:
        qWarning() << "unhandled PositionType";
        break;
    }
    return fileName;
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
