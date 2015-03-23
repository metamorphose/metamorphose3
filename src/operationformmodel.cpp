#include <QtCore/QtDebug>
#include "operationformmodel.h"

OperationFormModel::OperationFormModel(QObject *parent)
{

}

OperationFormModel::~OperationFormModel()
{

}

int OperationFormModel::columnCount(const QModelIndex &parent __attribute__ ((unused))) const
{
    return 2;
}

int OperationFormModel::rowCount(const QModelIndex &parent __attribute__ ((unused))) const
{
    return m_operations.size();
}

QVariant OperationFormModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        QString header;
        switch (section) {
        case 0:
            header = "";
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

QVariant OperationFormModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    QVariant data;
    if (role == Qt::ToolTipRole) {
        data = "tooltip data";
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QWidget *item = m_operations.at(index.row());
        switch (index.column()) {
        case 0:
            data = item->isEnabled();
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

void OperationFormModel::addOperation(OperationFormItem *operation)
{
    int size = m_operations.size();
    beginInsertRows(parentItem, size, size);
    m_operations.append(operation);
    endInsertRows();
}
