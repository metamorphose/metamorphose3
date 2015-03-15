#include <QtCore/QtDebug>
#include "diritem.h"

DirItem::DirItem(const DirItem::ItemData &data)
{
    m_itemData = data;
}

DirItem::~DirItem()
{
}

DirItem::ItemData DirItem::data() const
{
    return m_itemData;
}

QString DirItem::oldName(const bool &absolute) const
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

QString DirItem::newName(const bool &absolute) const
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

bool DirItem::rename(const long &index)
{
    m_itemData.newBaseName = QString("%1_new_%2")
            .arg(index + 1, 3, 10, QChar('0'))
            .arg(m_itemData.completeBaseName);
    m_itemData.newSuffix = m_itemData.completeSuffix;
    return true;
}

bool DirItem::itemCompare(DirItem *i, DirItem *j, Qt::SortOrder order)
{
    int compare = i->oldName(true).localeAwareCompare(j->oldName(true));
    if (order == Qt::AscendingOrder && compare < 0) {
        return true;
    }
    if (order == Qt::DescendingOrder && compare > 0) {
        return true;
    }
    return false;
}
