#ifndef OPERATIONFORMMODEL_H
#define OPERATIONFORMMODEL_H

#include <QtWidgets/QWidget>
#include <QtCore/QAbstractTableModel>
#include "operationformitem.h"


class OperationFormModel : public QAbstractTableModel
{
public:
    ~OperationFormModel();

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void addOperation(OperationFormItem *operation);
    bool isEmpty() const;

private:
    QModelIndex parentItem;
    QList<OperationFormItem*> itemsList;
};

#endif // OPERATIONFORMMODEL_H
