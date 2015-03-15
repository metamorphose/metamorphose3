#ifndef DIRITEM_H
#define DIRITEM_H
#include <QtCore>

class DirItem
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

    explicit DirItem(const ItemData &itemData);
    ~DirItem();

    ItemData data() const;
    QString oldName(const bool &absolute = false) const;
    QString newName(const bool &absolute = false) const;
    bool rename(const long &index);
    static bool itemCompare(DirItem *i, DirItem *j, Qt::SortOrder order);

private:
    DirItem::ItemData m_itemData;
};

#endif // DIRITEM_H
