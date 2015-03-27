#ifndef RENAMERITEM_H
#define RENAMERITEM_H

#include <QtCore>

class RenamerItem : public QObject
{
    Q_OBJECT

public:
    QString oldName(const bool &absolute = false) const;
    QString newName(const bool &absolute = false) const;
    bool applyRenameOps(const int &index);
    bool isNameChanged();
    bool hasWarning();
    bool hasError();
    static bool itemCompare(RenamerItem *i, RenamerItem *j, Qt::SortOrder order);

    QString absolutePath;
    QString completeBaseName;
    QString completeSuffix;
    bool isDir;
    QString newBaseName;
    QString newSuffix;

private:
    bool nameChanged = false;
    int errorCode = 0;
};

#endif // RENAMERITEM_H
