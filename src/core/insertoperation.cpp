#include "insertoperation.h"

/**
 * Performed for every item in the renamer list.
 */
void InsertOperation::operation(QString &name)
{
    QString parsedText = parseSubOps();

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
    case BeforeText:
        name.replace(textToSearch, parsedText + textToSearch, caseSensitivity);
        break;
    case AfterText:
        name.replace(textToSearch, textToSearch + parsedText, caseSensitivity);
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

void InsertOperation::setTextToSearch(const QString text)
{
    textToSearch = text;
}

void InsertOperation::setCaseSensitive(const bool isCaseSensitive)
{
    if (!isCaseSensitive) {
        caseSensitivity = Qt::CaseInsensitive;
    }
    else {
        caseSensitivity = Qt::CaseSensitive;
    }
}
