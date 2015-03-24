#ifndef RENAMERITEM_H
#define RENAMERITEM_H

#include <QtCore>

class RenamerItem// : public QObject
{
    //Q_OBJECT

public:
    struct ItemData {
      QString absolutePath;
      QString completeBaseName;
      QString completeSuffix;
      bool isDir;
      QString newBaseName;
      QString newSuffix;
    };

    explicit RenamerItem(const ItemData &itemData, QObject *parent = 0);
    ~RenamerItem();

    ItemData data() const;
    QString oldName(const bool &absolute = false) const;
    QString newName(const bool &absolute = false) const;
    void applyRenameOps(const long &index);
    bool isNameChanged();
    static bool itemCompare(RenamerItem *i, RenamerItem *j, Qt::SortOrder order);

private:
    bool nameChanged;
    RenamerItem::ItemData itemData;
};

#endif // RENAMERITEM_H
