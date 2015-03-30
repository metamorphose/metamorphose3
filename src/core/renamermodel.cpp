#include <QtCore/QtDebug>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtGui/QIcon>
#include <QtGui/QBrush>
#include "renamermodel.h"

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
        data = item->absolutePath;
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        RenamerItem *item = itemsList.at(index.row());
        switch (index.column()) {
        case 0:
            data = item->absolutePath;
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
        if (item->isDir) {
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

void RenamerModel::clear()
{
    if (!itemsList.isEmpty()) {
        beginResetModel();
        qDebug() << "Clearing items...";
        qDeleteAll(itemsList.begin(), itemsList.end());
        itemsList.clear();
        endResetModel();
    }
}

int RenamerModel::addFiles(const QStringList &fileList)
{
    int startSize = itemsList.size();
    int listSize = fileList.size();
    int endSize = startSize + listSize;

    qDebug() << "Adding" << listSize << "files...";

    beginInsertRows(parentItem, startSize, endSize - 1);

    QElapsedTimer timer;
    timer.start();

    for (int i = 0; i < listSize; i++) {
        addFile(QFileInfo(fileList.at(i)));
    }

    endInsertRows();
    int elapsedTime = timer.elapsed();
    int itemCount = endSize - startSize;
    qDebug() << "Loaded" << itemCount << "items in" << elapsedTime << "msec";
    QString message = tr("Loaded %n item(s)", "", itemCount);
    emit operationCompleted(message);
    return itemCount;
}

void RenamerModel::addFile(const QFileInfo &fileInfo)
{
    //qDebug() << "file:" << fileInfo.fileName();
    RenamerItem *item = new RenamerItem();
    item->absolutePath = fileInfo.absolutePath();
    item->completeBaseName = fileInfo.completeBaseName();
    item->completeSuffix = fileInfo.completeSuffix();
    item->isDir = fileInfo.isDir();
    itemsList.append(item);
}

int RenamerModel::addDirectories(const QStringList &directoryList,
                              const bool &recursive,
                              const QStringList nameFilters,
                              const bool &files,
                              const bool &folders,
                              const bool &hidden)
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
    qDebug() << "Adding" << directoryList.size() << "directories...";
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
        qWarning() << QString("Path doesn't exist: %1").arg(path);
        return false;
    }
    dir.setNameFilters(nameFilters);

    dir.setFilter(filter | QDir::NoDotAndDotDot);

    qDebug() << "Opening:" << path;

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
    qDebug() << "Loaded" << itemCount << "items in" << elapsedTime << "msec";
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

    if (order == Qt::AscendingOrder) {
        std::sort(itemsList.begin(), itemsList.end(), itemCompareAsc);
    }
    else {
        std::sort(itemsList.begin(), itemsList.end(), itemCompareDesc);
    }

    int elapsedTime = timer.elapsed();
    emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
    qDebug() << "Sorted" << itemCount << "items in" << elapsedTime << "msec";
    QString message = QString(tr("Sorted %n item(s)", "", itemCount));
    emit operationCompleted(message);
}

void RenamerModel::setOperations(OperationModel *operationModel)
{
    operations = operationModel;
}

int RenamerModel::applyRenamingOps()
{
    int itemCount = rowCount();
    if (itemCount == 0) {
        return false;
    }
    qDebug() << "Applying rules on" << itemCount << "items";
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
    qDebug() << "Applied rules on" << itemCount << "items in" << elapsedTime << "msec";
    QString message = tr("Applied rules on %n item(s)", "", itemCount);
    emit operationCompleted(message);
    return changedCount;
}

bool RenamerModel::renameItems()
{
    int itemCount = rowCount();
    if (itemCount == 0) {
        return false;
    }
    qDebug() << "Renaming" << itemCount << "items";
    QElapsedTimer timer;
    timer.start();

    QDir d;
    for (int i = 0; i < itemCount; ++i) {
        RenamerItem *item = itemsList.at(i);
        d.rename(item->oldName(true), item->newName(true));
    }
    int elapsedTime = timer.elapsed();
    emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
    qDebug() << "Renamed" << itemCount << "items in" << elapsedTime << "msec";
    QString message = tr("Renamed %n item(s)", "", itemCount);
    emit operationCompleted(message);
    return true;
}
