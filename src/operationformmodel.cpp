#include "operationformmodel.h"

Q_LOGGING_CATEGORY(M3GUI, "gui")

OperationFormModel::OperationFormModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    operations = new OperationModel();
}

OperationFormModel::~OperationFormModel()
{
    qDeleteAll(opFormList);
}

bool OperationFormModel::isEmpty() const
{
    return opFormList.isEmpty();
}

int OperationFormModel::columnCount(const QModelIndex &parent __attribute__ ((unused))) const
{
    return 2;
}

int OperationFormModel::rowCount(const QModelIndex &parent __attribute__ ((unused))) const
{
    return opFormList.size();
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
        OperationFormItem *opForm = opFormList.at(index.row());
        switch (index.column()) {
        case 0:
            //data = opForm->isEnabled();
            break;
        case 1:
            data = opForm->name();
            break;
        default:
            break;
        }
    }
    else if (role == Qt::CheckStateRole && index.column() == 0) {
        OperationFormItem *opForm = opFormList.at(index.row());
        if (opForm->isEnabled()) {
            data = Qt::Checked;
        }
        else {
            data = Qt::Unchecked;
        }
    }
    return data;
}

bool OperationFormModel::removeRows(int row, int count,
                                    const QModelIndex &parent)
{
    if ((count < 1) || (row < 0) || ((row + count) > rowCount())) {
        return false;
    }
    beginRemoveRows(parentItem, row, row + count - 1);
    opFormList.begin();
    for (int i = 0; i < count; ++i) {
        OperationFormItem *opForm = opFormList.takeAt(row);
        qCDebug(M3GUI) << "Remove" << opForm->name() << "at pos" << row + i;
        delete opForm;
    }
    endRemoveRows();
    return true;
}

void OperationFormModel::addOperationForm(OperationFormItem *opForm)
{
    int size = opFormList.size();
    beginInsertRows(parentItem, size, size);
    qCDebug(M3GUI) << "Append" << opForm->name();
    opFormList.append(opForm);
    endInsertRows();
}

OperationFormItem* OperationFormModel::getOperationAt(int row)
{
    return opFormList.at(row);
}

OperationModel* OperationFormModel::getOperations()
{
    operations->clear();
    qCDebug(M3GUI) << "Configuring" << opFormList.size() << "operation(s)";
    for (OperationFormItem *opForm : opFormList) {
        if (opForm->isEnabled()) {
            opForm->configureOperation();
            operations->addOperation(opForm->getOperation());
        }
    }
    return operations;
}
