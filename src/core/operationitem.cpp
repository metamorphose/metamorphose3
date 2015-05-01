#include "operationitem.h"

void OperationItem::applyOperation(int itemPosition, std::pair<QString, QString> &name)
{
    if (applyToName) {
        operation(itemPosition, name.first);
    }
    if (applyToExtension) {
        operation(itemPosition, name.second);
    }
}

/**
 * Innermost loop!
 */
void OperationItem::parseSubOps(int itemPosition, QString &text)
{
    qCDebug(M3CORE) << "parsing for subops" << text;

    QStringList segments = text.split("::", QString::SkipEmptyParts);

    for (int i = 0; i < segments.size(); ++i) {
        QString segment = segments.at(i);

        if (segment == "numb") {
            segments[i] = QString::number(itemPosition);
        }
        if (segment == "date") {
            QDateTime datetime = QDateTime::currentDateTime();
            segments[i] = datetime.toString("yyyy-MM-dd");
        }
        if (segment == "time") {
            QDateTime datetime = QDateTime::currentDateTime();
            segments[i] = datetime.toString("hh-mm-ss");
        }
        qCDebug(M3CORE) << segment;

        text = segments.join("");
    }
}

void OperationItem::setApplyToName(bool apply)
{
    applyToName = apply;
}

void OperationItem::setApplyToExtension(bool apply)
{
    applyToExtension = apply;
}
