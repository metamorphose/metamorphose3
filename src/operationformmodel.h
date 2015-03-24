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
                  int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    void addOperation(OperationFormItem *operation);
    bool isEmpty() const;

private:
    QModelIndex parentItem;
    QList<OperationFormItem*> itemsList;
};

#endif // OPERATIONFORMMODEL_H
