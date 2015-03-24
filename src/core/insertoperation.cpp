#include "insertoperation.h"

InsertOperation::InsertOperation()
{

}

InsertOperation::~InsertOperation()
{

}

QString InsertOperation::applyOperation(int opPosition, QString fileName)
{
    QString parsedText = QString("%1").arg(opPosition);

    switch (positionType) {
    case Prefix:
        fileName.prepend(parsedText);
        break;
    case Suffix:
        fileName.append(parsedText);
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
