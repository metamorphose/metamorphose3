#include <QtCore/QtDebug>
#include "renameritem.h"

RenamerItem::RenamerItem(QObject *parent)
    : QObject(parent)
{

}

QString RenamerItem::oldName(const bool &absolute) const
{
    QString oldName;
    if (!completeSuffix.isEmpty()) {
        oldName = QString("%1.%2")
                        .arg(completeBaseName)
                        .arg(completeSuffix);
    }
    else {
        oldName = completeBaseName;
    }

    if (absolute) {
        oldName = QString("%1/%2").arg(absolutePath).arg(oldName);
    }
    return oldName;
}

QString RenamerItem::newName(const bool &absolute) const
{
    if (newBaseName.isEmpty()) {
        return oldName(absolute);
    }
    QString newName;
    if (!newSuffix.isEmpty()) {
        newName = QString("%1.%2")
                        .arg(newBaseName)
                        .arg(newSuffix);
    }
    else {
        newName = newBaseName;
    }

    if (absolute) {
        newName = QString("%1/%2").arg(absolutePath).arg(newName);
    }
    return newName;
}

bool RenamerItem::isNameChanged()
{
    return nameChanged;
}

bool RenamerItem::hasWarning()
{
    return false;
}

bool RenamerItem::hasError()
{
    return false;
}

bool RenamerItem::applyRenameOps(const int &index, OperationModel* operations)
{
    newBaseName.clear();
    newSuffix.clear();

    newBaseName = operations->applyOperations(index, completeBaseName);
    newSuffix = completeSuffix;

    qDebug() << completeBaseName << "=>" << newBaseName;

    if (newBaseName != completeBaseName
        || newSuffix != completeSuffix) {
        nameChanged = true;
    }
    else {
        nameChanged = false;
    }
    return nameChanged;
}

bool RenamerItem::itemCompare(RenamerItem *i, RenamerItem *j, Qt::SortOrder order)
{
    if (i->isDir != j->isDir) {
        return i->isDir;
    }
    int compare = i->oldName(true).localeAwareCompare(j->oldName(true));
    if (order == Qt::AscendingOrder && compare < 0) {
        return true;
    }
    if (order == Qt::DescendingOrder && compare > 0) {
        return true;
    }
    return false;
}
