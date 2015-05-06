#ifndef RENAMERITEM_H
#define RENAMERITEM_H

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QElapsedTimer>
#include <QtCore/QDateTime>
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
    bool isNameChanged() const;
    bool hasWarning() const;
    bool hasError() const;
    static bool itemCompare(const RenamerItem *i, const RenamerItem *j,
                            Qt::SortOrder order);
    void setOldName(QString name, QString extension);
    void setPath(QString path);
    QString path() const;
    void setIsDir(bool isDir);
    bool isDir() const;
    void setCreated(QDateTime created);
    void setLastModified(QDateTime lastModified);

private:
    std::pair<QString, QString> oldNameSplit;
    std::pair<QString, QString> newNameSplit;
    QString absolutePath;
    bool nameChanged = false;
    int errorCode = 0;
    bool isDirectory;
    QDateTime created;
    QDateTime lastModified;
};

#endif // RENAMERITEM_H
