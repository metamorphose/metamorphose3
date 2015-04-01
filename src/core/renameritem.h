#ifndef RENAMERITEM_H
#define RENAMERITEM_H

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QElapsedTimer>
#include "operationmodel.h"

class RenamerItem : public QObject
{
    Q_OBJECT

public:
    explicit RenamerItem(QObject *parent = 0);

    QString oldName(const bool &absolute = false) const;
    QString newName(const bool &absolute = false) const;
    bool applyRenameOps(const int &index,
                        OperationModel* operations);
    bool isNameChanged();
    bool hasWarning();
    bool hasError();
    static bool itemCompare(RenamerItem *i, RenamerItem *j, Qt::SortOrder order);
    void setOldName(QString name, QString extension);
    void setPath(QString path);
    QString path();

    bool isDir;

private:
    std::pair<QString, QString> oldNameSplit;
    std::pair<QString, QString> newNameSplit;
    QString absolutePath;
    bool nameChanged = false;
    int errorCode = 0;
};

#endif // RENAMERITEM_H
