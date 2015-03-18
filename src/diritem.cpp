#include <QtCore/QtDebug>
#include "renameritem.h"

RenamerItem::RenamerItem(const RenamerItem::ItemData &data)
{
    m_itemData = data;
}

RenamerItem::~RenamerItem()
{
}

RenamerItem::ItemData RenamerItem::data() const
{
    return m_itemData;
}

QString RenamerItem::oldName(const bool &absolute) const
{
    QString oldName;
    if (!m_itemData.completeSuffix.isEmpty()) {
        oldName = QString("%1.%2")
                        .arg(m_itemData.completeBaseName)
                        .arg(m_itemData.completeSuffix);
    }
    else {
        oldName = m_itemData.completeBaseName;
    }

    if (absolute) {
        oldName = QString("%1/%2").arg(m_itemData.absolutePath).arg(oldName);
    }
    return oldName;
}

QString RenamerItem::newName(const bool &absolute) const
{
    if (m_itemData.newBaseName.isEmpty()) {
        return oldName(absolute);
    }
    QString newName;
    if (!m_itemData.newSuffix.isEmpty()) {
        newName = QString("%1.%2")
                        .arg(m_itemData.newBaseName)
                        .arg(m_itemData.newSuffix);
    }
    else {
        newName = m_itemData.newBaseName;
    }

    if (absolute) {
        newName = QString("%1/%2").arg(m_itemData.absolutePath).arg(newName);
    }
    return newName;
}

bool RenamerItem::rename(const long &index)
{
    m_itemData.newBaseName = QString("%1_new_%2")
            .arg(index + 1, 3, 10, QChar('0'))
            .arg(m_itemData.completeBaseName);
    m_itemData.newSuffix = m_itemData.completeSuffix;
    return true;
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
