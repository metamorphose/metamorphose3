#ifndef DIRITEM_H
#define DIRITEM_H
#include <QtCore>

class RenamerItem
{
public:
    struct ItemData {
      QString absolutePath;
      QString completeBaseName;
      QString completeSuffix;
      bool isDir;
      QString newBaseName;
      QString newSuffix;
    };

    explicit RenamerItem(const ItemData &itemData);
    ~RenamerItem();

    ItemData data() const;
    QString oldName(const bool &absolute = false) const;
    QString newName(const bool &absolute = false) const;
    bool rename(const long &index);
    static bool itemCompare(RenamerItem *i, RenamerItem *j, Qt::SortOrder order);

private:
    RenamerItem::ItemData m_itemData;
};

#endif // DIRITEM_H
