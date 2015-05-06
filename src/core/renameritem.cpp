#include "renameritem.h"

Q_LOGGING_CATEGORY(M3CORE, "core")

RenamerItem::RenamerItem(QObject *parent)
    : QObject(parent)
{

}

void RenamerItem::setOldName(QString name, QString extension)
{
    oldNameSplit.first = name;
    oldNameSplit.second = extension;
}

void RenamerItem::setPath(QString path)
{
    absolutePath = path;
}

/**
 * @return the absolute path of the item.
 */
QString RenamerItem::path() const
{
    return absolutePath;
}

void RenamerItem::setIsDir(bool isDir)
{
    isDirectory = isDir;
}

bool RenamerItem::isDir() const
{
    return isDirectory;
}

void RenamerItem::setCreated(QDateTime created)
{
    this->created = created;
}

void RenamerItem::setLastModified(QDateTime lastModified)
{
    this->lastModified = lastModified;
}

QString RenamerItem::oldName(const bool &absolute) const
{
    QString oldName;
    if (!oldNameSplit.second.isEmpty()) {
        oldName = QString("%1.%2")
                        .arg(oldNameSplit.first)
                        .arg(oldNameSplit.second);
    }
    else {
        oldName = oldNameSplit.first;
    }

    if (absolute) {
        oldName = QString("%1/%2").arg(absolutePath).arg(oldName);
    }
    return oldName;
}

QString RenamerItem::newName(const bool &absolute) const
{
    if (newNameSplit.first.isEmpty()) {
        return oldName(absolute);
    }
    QString newName;
    if (!newNameSplit.second.isEmpty()) {
        newName = QString("%1.%2")
                        .arg(newNameSplit.first)
                        .arg(newNameSplit.second);
    }
    else {
        newName = newNameSplit.first;
    }

    if (absolute) {
        newName = QString("%1/%2").arg(absolutePath).arg(newName);
    }
    return newName;
}

bool RenamerItem::isNameChanged() const
{
    return nameChanged;
}

bool RenamerItem::hasWarning() const
{
    return false;
}

bool RenamerItem::hasError() const
{
    return false;
}

bool RenamerItem::applyRenameOps(const int &index, OperationModel* operations)
{
    newNameSplit.first.clear();
    newNameSplit.second.clear();

    newNameSplit = operations->applyOperations(index, oldNameSplit);

    qCDebug(M3CORE) << oldNameSplit.first << oldNameSplit.second
                    << "=>" << newNameSplit.first << newNameSplit.second;

    nameChanged = (newNameSplit != oldNameSplit);
    return nameChanged;
}

bool RenamerItem::itemCompare(const RenamerItem *i, const RenamerItem *j, Qt::SortOrder order)
{
    if (i->isDirectory != j->isDirectory) {
        return i->isDirectory;
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
