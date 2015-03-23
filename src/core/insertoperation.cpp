#include "insertoperation.h"

InsertOperation::InsertOperation()
{

}

InsertOperation::~InsertOperation()
{

}

QString InsertOperation::applyOperation(int opPosition)
{
    return QString("%1").arg(opPosition);
}
