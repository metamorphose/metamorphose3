#ifndef RENAMERITEM_H
#define RENAMERITEM_H

#include <QtCore>

class RenamerItem : public QObject
{
    Q_OBJECT

public:
    explicit RenamerItem(QObject *parent = 0);

    QString oldName(const bool &absolute = false) const;
    QString newName(const bool &absolute = false) const;
    void applyRenameOps(const long &index);
    bool isNameChanged();
    static bool itemCompare(RenamerItem *i, RenamerItem *j, Qt::SortOrder order);

    QString absolutePath;
    QString completeBaseName;
    QString completeSuffix;
    bool isDir;
    QString newBaseName;
    QString newSuffix;

private:
    bool nameChanged;
};

#endif // RENAMERITEM_H
