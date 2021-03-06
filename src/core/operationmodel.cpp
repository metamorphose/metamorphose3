#include "operationmodel.h"

OperationModel::OperationModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

OperationModel::~OperationModel()
{
    qDeleteAll(itemsList);
}

/**
 * Removes all items from the model.
 */
void OperationModel::clear()
{
    if (!itemsList.isEmpty()) {
        beginResetModel();
        qCDebug(M3CORE) << "Clearing operations...";
        itemsList.clear();
        endResetModel();
    }
}

bool OperationModel::isEmpty() const
{
    return itemsList.isEmpty();
}

int OperationModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

int OperationModel::rowCount(const QModelIndex &parent) const
{
    return itemsList.size();
}

QVariant OperationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        QString header;
        switch (section) {
        case 0:
            header = QString(" ");
            break;
        case 1:
            header = tr("Type");
            break;
        default:
            break;
        }
        return header;
    }
    else if (orientation == Qt::Vertical) {
        return section + 1;
    }
    return QVariant();
}

QVariant OperationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    QVariant data;
    if (role == Qt::ToolTipRole) {
        data = "tooltip data";
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            data = true;
            break;
        case 1:
            data = "Insert";
            break;
        default:
            break;
        }
    }
    return data;
}

void OperationModel::addOperation(OperationItem *operation)
{
    int size = itemsList.size();
    beginInsertRows(parentItem, size, size);
    itemsList.append(operation);
    endInsertRows();
}

void OperationModel::preProcessOperations()
{
    for (OperationItem *op : itemsList) {
       op->preprocess();
    }
}

std::pair<QString, QString> OperationModel::applyOperations(const int &index,
                                                        std::pair<QString, QString> oldName)
{
    std::pair<QString, QString> newName = std::make_pair(QString("%1").arg(oldName.first),
                                                         QString("%1").arg(oldName.second));
    for (OperationItem *op : itemsList) {
       op->applyOperation(index, newName);
    }
    return newName;
}
