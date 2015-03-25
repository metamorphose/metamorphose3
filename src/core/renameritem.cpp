#include <QtCore/QtDebug>
#include "renameritem.h"

RenamerItem::RenamerItem(QObject *parent)
{
    nameChanged = false;
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

void RenamerItem::applyRenameOps(const long &index)
{
    newBaseName = QString("%1_new_%2")
            .arg(index + 1, 3, 10, QChar('0'))
            .arg(completeBaseName);
    newSuffix = completeSuffix;

    if (newBaseName != completeBaseName
        || newSuffix != completeSuffix) {
        nameChanged = true;
    }
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
