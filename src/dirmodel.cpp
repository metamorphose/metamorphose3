#include <QtCore/QtDebug>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "dirmodel.h"

DirModel::DirModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    clear();
}

DirModel::~DirModel()
{
    qDeleteAll(dirItems);
}

int DirModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

int DirModel::rowCount(const QModelIndex &parent) const
{
    return dirItems.size();
}

QVariant DirModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    QVariant data;
    if (role == Qt::ToolTipRole) {
        DirItem *item = dirItems.at(index.row());
        data = item->data().absolutePath;
    }
    else if (role == Qt::DisplayRole) {
        DirItem *item = dirItems.at(index.row());
        switch (index.column()) {
        case 0:
            data = item->data().absolutePath;
            break;
        case 1:
            data = item->oldName();
            break;
        case 2:
            data = item->newName();
            break;
        default:
            break;
        }
    }
    //qDebug() << "item:" << data;
    return data;
}

QVariant DirModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        QString header;
        switch (section) {
        case 0:
            header = QString("Location");
            break;
        case 1:
            header = QString("Original Name");
            break;
        case 2:
            header = QString("New Name");
            break;
        default:
            break;
        }
        return header;
    }
    else if (orientation == Qt::Vertical) {
        return locale.toString(section + 1);
    }
    return QVariant();
}

void DirModel::clear()
{
    if (!dirItems.isEmpty()) {
        beginResetModel();
        qDebug() << "Clearing items...";
        dirItems.clear();
        endResetModel();
    }
}

void DirModel::addFiles(const QStringList &fileList)
{
    int startSize = dirItems.size();
    int listSize = fileList.size();
    int endSize = startSize + listSize;

    qDebug() << "Adding" << listSize << "files...";

    beginInsertRows(parentItem, startSize, endSize - 1);

    for (int i = 0; i < listSize; i++) {
        addFile(fileList.at(i));
    }
    endInsertRows();
}

void DirModel::addFile(const QString &file)
{
    addFile(QFileInfo(file));
}

void DirModel::addFile(const QFileInfo &fileInfo)
{
    //qDebug() << "file:" << fileInfo.fileName();

    DirItem::ItemData itemData;
    itemData.absolutePath = fileInfo.absolutePath();
    itemData.completeBaseName = fileInfo.completeBaseName();
    itemData.completeSuffix = fileInfo.completeSuffix();
    itemData.isDir = fileInfo.isDir();

    DirItem *dirItem = new DirItem(itemData);
    dirItems << dirItem;
}

void DirModel::addDirectories(const QStringList &directoryList, const bool &recursive)
{
    qDebug() << "Adding" << directoryList.size() << "directories...";
    for (int i = 0; i < directoryList.size(); i++) {
        addDirectory(directoryList.at(i), recursive);
    }
}

bool DirModel::addDirectory(const QString &path, const bool recursive)
{
    QDir dir(path);
    if (!dir.exists(path)) {
        qWarning() << QString("Path doesn't exist: %1").arg(path);
        return false;
    }

    QStringList nameFilters;
    nameFilters << "*";
    dir.setNameFilters(nameFilters);

    QDir::Filters filter = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden;
    dir.setFilter(filter);

    qDebug() << "Opening:" << path;

    QDirIterator::IteratorFlags flags;// = QDirIterator::NoIteratorFlags;
    if (recursive) {
        flags = QDirIterator::Subdirectories;
    }
    QDirIterator it (dir, flags);

    QElapsedTimer timer;
    timer.start();

    int startSize = dirItems.size();
    while (it.hasNext()) {
        it.next();
        addFile(it.fileInfo());
    }
    int endSize = dirItems.size();

    beginInsertRows(parentItem, startSize, endSize - 1);
    endInsertRows();

    int elapsedTime = timer.elapsed();
    qDebug() << "Loaded" << endSize - startSize << "items in" << elapsedTime << "msec";
    return true;
}

bool DirModel::applyRenamingRules()
{
    int itemCount = rowCount();
    if (itemCount > 0) {
        qDebug() << "Apply rules on" << itemCount << "items";
        for (int i = 0; i < itemCount; ++i) {
            dirItems.at(i)->rename(i);
        }
        emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
        return true;
    }
    return false;
}

bool DirModel::renameItems()
{
    int itemCount = rowCount();
    if (itemCount > 0) {
        qDebug() << "Renaming" << itemCount << "items";
        QDir d;
        for (int i = 0; i < itemCount; ++i) {
            DirItem dirItem = *dirItems.at(i);
            d.rename(dirItem.oldName(true), dirItem.newName(true));
        }
        //emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
        return true;
    }
    return false;
}
