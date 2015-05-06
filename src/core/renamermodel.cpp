#include <QtGui/QIcon>
#include <QtGui/QBrush>
#include "renamermodel.h"
#include <future>

RenamerModel::RenamerModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

RenamerModel::~RenamerModel()
{
    qDeleteAll(itemsList);
}

Qt::ItemFlags RenamerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
}

/**
 * @return @c true if the model contains no items, @c false otherwise
 */
bool RenamerModel::isEmpty() const
{
    return itemsList.isEmpty();
}

int RenamerModel::columnCount(const QModelIndex &parent __attribute__ ((unused))) const
{
    return 3;
}

int RenamerModel::rowCount(const QModelIndex &parent __attribute__ ((unused))) const
{
    return itemsList.size();
}

QVariant RenamerModel::data(const QModelIndex &index, int role) const
{
    QVariant data;
    if (!index.isValid()) {
        return data;
    }
    if (role == Qt::ToolTipRole) {
        RenamerItem *item = itemsList.at(index.row());
        data = item->path();
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        RenamerItem *item = itemsList.at(index.row());
        switch (index.column()) {
        case 0:
            data = item->path();
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
    // TODO: there should be no GUI code in this class
    else if (role == Qt::BackgroundRole) {
        RenamerItem *item = itemsList.at(index.row());
        if (item->hasError()) {
            return QBrush(QColor(255, 0, 0, 20));
        }
        else if (item->hasWarning()) {
            return QBrush(QColor(255, 255, 0, 20));
        }
        else if (item->isNameChanged()) {
            return QBrush(QColor(0, 255, 0, 10));
        }
    }
    else if (role == Qt::DecorationRole && index.column() == 0) {
        RenamerItem *item = itemsList.at(index.row());
        if (item->isDir()) {
            return QIcon::fromTheme("folder");
        }
        return QIcon::fromTheme("text-x-generic");
    }
    return data;
}

QVariant RenamerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        QString header;
        switch (section) {
        case 0:
            header = tr("Location");
            break;
        case 1:
            header = tr("Original Name");
            break;
        case 2:
            header = tr("New Name");
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

/**
 * Removes all items from the model and deletes them.
 */
void RenamerModel::clearAndDelete()
{
    if (!itemsList.isEmpty()) {
        beginResetModel();
        qCDebug(M3CORE) << "Clearing items...";
        qDeleteAll(itemsList.begin(), itemsList.end());
        itemsList.clear();
        endResetModel();
    }
}

/**
 * Add a list of files to the model.
 * @param fileList
 * @return the number of files added.
 */
int RenamerModel::addFiles(const QStringList &fileList)
{
    int listSize = fileList.size();
    qCDebug(M3CORE) << "Adding" << listSize << "files...";

    QElapsedTimer timer;
    timer.start();

    int startSize = itemsList.size();
    for (int i = 0; i < listSize; i++) {
        addFile(QFileInfo(fileList.at(i)));
    }
    int endSize = itemsList.size();

    beginInsertRows(parentItem, startSize, endSize - 1);
    endInsertRows();

    int elapsedTime = timer.elapsed();
    int itemCount = endSize - startSize;
    qCDebug(M3CORE) << "Loaded" << itemCount << "items in" << elapsedTime << "msec";
    QString message = tr("Loaded %n item(s)", "", itemCount);
    emit operationCompleted(message);
    return itemCount;
}

bool RenamerModel::addFile(const QFileInfo &fileInfo)
{
    if (!fileInfo.isWritable()) {
        qCWarning(M3CORE) << "Not writable:" << fileInfo.absoluteFilePath();
        return false;
    }
    RenamerItem *item = new RenamerItem();
    item->setPath(fileInfo.absolutePath());
    item->setOldName(fileInfo.completeBaseName(), fileInfo.completeSuffix());
    item->setIsDir(fileInfo.isDir());
    item->setCreated(fileInfo.created());
    item->setLastModified(fileInfo.lastModified());
    itemsList.append(item);
    return true;
}

int RenamerModel::addDirectories(const QStringList &directoryList,
                              const bool &recursive,
                              const QStringList nameFilters,
                              const bool files,
                              const bool folders,
                              const bool hidden)
{
    QDir::Filters filter;
    if (files) {
        filter = QDir::Files;
    }
    if (folders) {
        filter = filter | QDir::Dirs;
    }
    if (hidden) {
        filter = filter | QDir::Hidden;
    }
    qCDebug(M3CORE) << "Adding" << directoryList.size() << "directories...";
    int itemCount = 0;
    for (int i = 0; i < directoryList.size(); i++) {
        itemCount += addDirectory(directoryList.at(i), recursive, nameFilters, filter);
    }
    return itemCount;
}

int RenamerModel::addDirectory(const QString &path,
                            const bool recursive,
                            const QStringList &nameFilters,
                            const QDir::Filters &filter)
{
    QDir dir(path);
    if (!dir.exists(path)) {
        qCWarning(M3CORE) << QString("Path doesn't exist: %1").arg(path);
        return false;
    }
    dir.setNameFilters(nameFilters);

    dir.setFilter(filter | QDir::NoDotAndDotDot);

    qCDebug(M3CORE) << "Opening:" << path;

    QDirIterator::IteratorFlags flags;
    if (recursive) {
        flags = QDirIterator::Subdirectories;
    }
    QDirIterator it (dir, flags);

    QElapsedTimer timer;
    timer.start();

    int startSize = itemsList.size();
    while (it.hasNext()) {
        it.next();
        addFile(it.fileInfo());
    }
    int endSize = itemsList.size();

    beginInsertRows(parentItem, startSize, endSize - 1);
    endInsertRows();

    int elapsedTime = timer.elapsed();
    int itemCount = endSize - startSize;
    qCDebug(M3CORE) << "Loaded" << itemCount << "items in" << elapsedTime << "msec";
    QString message = QString(tr("Loaded %n item(s)", "", itemCount));
    emit operationCompleted(message);
    return itemCount;
}

bool itemCompareAsc(RenamerItem *i, RenamerItem *j)
{
    return RenamerItem::itemCompare(i, j, Qt::AscendingOrder);
}
bool itemCompareDesc(RenamerItem *i, RenamerItem *j)
{
    return RenamerItem::itemCompare(i, j, Qt::DescendingOrder);
}

void RenamerModel::sort(int column, Qt::SortOrder order)
{
    int itemCount = rowCount();
    if (itemCount == 0) {
        return;
    }

    QElapsedTimer timer;
    timer.start();

    int grainsize = std::max(1000, itemCount / 2);

    if (order == Qt::AscendingOrder) {
        async_sort(itemsList.begin(), itemCount, grainsize, itemCompareAsc);
    }
    else {
        async_sort(itemsList.begin(), itemCount, grainsize, itemCompareDesc);
    }

    int elapsedTime = timer.elapsed();
    emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
    qCDebug(M3CORE) << "Sorted" << itemCount << "items in" << elapsedTime << "msec";
    QString message = QString(tr("Sorted %n item(s)", "", itemCount));
    emit operationCompleted(message);
}

void RenamerModel::async_sort(QList<RenamerItem*>::iterator begin,
                              const int length, const int grainsize,
                              std::function<bool(RenamerItem*, RenamerItem*)> compareFunction)
{
    if (length < grainsize) {
        std::sort(begin, begin + length, compareFunction);
    }
    else {
        int half = length/2;
        int adjust = length%2;
        // call async
        std::future<void> future = std::async(std::launch::async,
                                              &RenamerModel::async_sort, this,
                                              begin, half-adjust, grainsize, compareFunction);
        // call blocking
        async_sort(begin + half, half+adjust, grainsize, compareFunction);
        future.wait();
        // merge as we go along
        std::inplace_merge(begin, begin + half, begin + length, compareFunction);
    }
}

void RenamerModel::setOperations(OperationModel *operationModel)
{
    operations = operationModel;
}

int RenamerModel::applyRenamingOps()
{
    int itemCount = rowCount();
    if (itemCount == 0 || operations->isEmpty()) {
        return 0;
    }
    qCDebug(M3CORE) << "Applying operations on" << itemCount << "items";
    QElapsedTimer timer;
    timer.start();

    int changedCount = 0;
    for (int i = 0; i < itemCount; ++i) {
        bool nameChanged = itemsList.at(i)->applyRenameOps(i, operations);
        if (nameChanged) {
            changedCount += 1;
        }
    }
    int elapsedTime = timer.elapsed();
    emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
    qCDebug(M3CORE) << "Applied rules on" << itemCount << "items in" << elapsedTime << "msec";
    QString message = tr("Applied rules on %n item(s)", "", itemCount);
    emit operationCompleted(message);
    return changedCount;
}

int RenamerModel::renameItems()
{
    int itemCount = rowCount();
    if (itemCount == 0) {
        return 0;
    }
    qCDebug(M3CORE) << "Renaming" << itemCount << "items";
    QElapsedTimer timer;
    timer.start();

    QDir d;
    int renamedCount = 0;
    for (int i = 0; i < itemCount; ++i) {
        RenamerItem *item = itemsList.at(i);
        bool renamed = d.rename(item->oldName(true), item->newName(true));
        if (renamed) {
            renamedCount += 1;
        }
    }
    int elapsedTime = timer.elapsed();
    emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
    qCDebug(M3CORE) << "Renamed" << itemCount << "items in" << elapsedTime << "msec";
    QString message = tr("Renamed %n item(s)", "", itemCount);
    emit operationCompleted(message);
    return renamedCount;
}
