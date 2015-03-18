#include <QtCore/QtDebug>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtGui/QIcon>
#include "renamermodel.h"

RenamerModel::RenamerModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    clear();
}

RenamerModel::~RenamerModel()
{
    qDeleteAll(dirItems);
}

Qt::ItemFlags RenamerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
}

int RenamerModel::columnCount(const QModelIndex &parent __attribute__ ((unused))) const
{
    return 3;
}

int RenamerModel::rowCount(const QModelIndex &parent __attribute__ ((unused))) const
{
    return dirItems.size();
}

QVariant RenamerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    QVariant data;
    if (role == Qt::ToolTipRole) {
        RenamerItem *item = dirItems.at(index.row());
        data = item->data().absolutePath;
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        RenamerItem *item = dirItems.at(index.row());
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
    // TODO: there should be no GUI code in this class
    if (role == Qt::DecorationRole && index.column() == 0) {
        RenamerItem *item = dirItems.at(index.row());
        if (item->data().isDir) {
            return QIcon::fromTheme("folder");
        }
        return QIcon::fromTheme("text-x-generic");
    }
    //qDebug() << "item:" << data;
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

void RenamerModel::clear()
{
    if (!dirItems.isEmpty()) {
        beginResetModel();
        qDebug() << "Clearing items...";
        dirItems.clear();
        endResetModel();
    }
}

void RenamerModel::addFiles(const QStringList &fileList)
{
    int startSize = dirItems.size();
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
    QString message = QString(tr("Loaded %n item(s)", "", itemCount));
    emit operationCompleted(message);
}

void RenamerModel::addFile(const QFileInfo &fileInfo)
{
    //qDebug() << "file:" << fileInfo.fileName();

    RenamerItem::ItemData itemData;
    itemData.absolutePath = fileInfo.absolutePath();
    itemData.completeBaseName = fileInfo.completeBaseName();
    itemData.completeSuffix = fileInfo.completeSuffix();
    itemData.isDir = fileInfo.isDir();

    RenamerItem *dirItem = new RenamerItem(itemData);
    dirItems << dirItem;
}

void RenamerModel::addDirectories(const QStringList &directoryList,
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
    for (int i = 0; i < directoryList.size(); i++) {
        addDirectory(directoryList.at(i), recursive, nameFilters, filter);
    }
}

bool RenamerModel::addDirectory(const QString &path,
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

    int startSize = dirItems.size();
    while (it.hasNext()) {
        it.next();
        addFile(it.fileInfo());
    }
    int endSize = dirItems.size();

    beginInsertRows(parentItem, startSize, endSize - 1);
    endInsertRows();

    int elapsedTime = timer.elapsed();
    int itemCount = endSize - startSize;
    qDebug() << "Loaded" << itemCount << "items in" << elapsedTime << "msec";
    QString message = QString(tr("Loaded %n item(s)", "", itemCount));
    emit operationCompleted(message);
    return true;
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
        std::sort(dirItems.begin(), dirItems.end(), itemCompareAsc);
    }
    else {
        std::sort(dirItems.begin(), dirItems.end(), itemCompareDesc);
    }

    int elapsedTime = timer.elapsed();
    emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
    qDebug() << "Sorted" << itemCount << "items in" << elapsedTime << "msec";
    QString message = QString(tr("Sorted %n item(s)", "", itemCount));
    emit operationCompleted(message);
}

bool RenamerModel::applyRenamingRules()
{
    int itemCount = rowCount();
    if (itemCount == 0) {
        return false;
    }
    qDebug() << "Applying rules on" << itemCount << "items";
    QElapsedTimer timer;
    timer.start();

    for (int i = 0; i < itemCount; ++i) {
        dirItems.at(i)->rename(i);
    }
    int elapsedTime = timer.elapsed();
    emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
    qDebug() << "Applyed rules on" << itemCount << "items in" << elapsedTime << "msec";
    QString message = QString(tr("Applied rules on %n item(s)", "", itemCount));
    emit operationCompleted(message);
    return true;
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
        RenamerItem dirItem = *dirItems.at(i);
        d.rename(dirItem.oldName(true), dirItem.newName(true));
    }
    int elapsedTime = timer.elapsed();
    emit dataChanged(createIndex(-1,0), createIndex(itemCount,columnCount()));
    qDebug() << "Renamed" << itemCount << "items in" << elapsedTime << "msec";
    QString message = QString(tr("Renamed %n item(s)", "", itemCount));
    emit operationCompleted(message);
    return true;
}
