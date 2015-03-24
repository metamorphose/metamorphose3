#include <QtCore/QtDebug>
#include "renameritem.h"

RenamerItem::RenamerItem(const RenamerItem::ItemData &data, QObject *parent)
{
    itemData = data;
    nameChanged = false;
}

RenamerItem::~RenamerItem()
{
}

RenamerItem::ItemData RenamerItem::data() const
{
    return itemData;
}

QString RenamerItem::oldName(const bool &absolute) const
{
    QString oldName;
    if (!itemData.completeSuffix.isEmpty()) {
        oldName = QString("%1.%2")
                        .arg(itemData.completeBaseName)
                        .arg(itemData.completeSuffix);
    }
    else {
        oldName = itemData.completeBaseName;
    }

    if (absolute) {
        oldName = QString("%1/%2").arg(itemData.absolutePath).arg(oldName);
    }
    return oldName;
}

QString RenamerItem::newName(const bool &absolute) const
{
    if (itemData.newBaseName.isEmpty()) {
        return oldName(absolute);
    }
    QString newName;
    if (!itemData.newSuffix.isEmpty()) {
        newName = QString("%1.%2")
                        .arg(itemData.newBaseName)
                        .arg(itemData.newSuffix);
    }
    else {
        newName = itemData.newBaseName;
    }

    if (absolute) {
        newName = QString("%1/%2").arg(itemData.absolutePath).arg(newName);
    }
    return newName;
}

bool RenamerItem::isNameChanged()
{
    return nameChanged;
}

void RenamerItem::applyRenameOps(const long &index)
{
    itemData.newBaseName = QString("%1_new_%2")
            .arg(index + 1, 3, 10, QChar('0'))
            .arg(itemData.completeBaseName);
    itemData.newSuffix = itemData.completeSuffix;

    if (itemData.newBaseName != itemData.completeBaseName
        || itemData.newSuffix != itemData.completeSuffix) {
        nameChanged = true;
    }
}

bool RenamerItem::itemCompare(RenamerItem *i, RenamerItem *j, Qt::SortOrder order)
{
    if (i->data().isDir != j->data().isDir) {
        return i->data().isDir;
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
