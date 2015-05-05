#ifndef OPERATIONFORMMODEL_H
#define OPERATIONFORMMODEL_H

#include <QtWidgets/QWidget>
#include <QtCore/QAbstractTableModel>
#include "operationformitem.h"
#include "core/operationmodel.h"

class OperationFormModel : public QAbstractTableModel
{
public:
    explicit OperationFormModel(QObject *parent = 0);
    ~OperationFormModel();

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                  const QModelIndex &destinationParent, int destinationChild) override;
    void addOperationForm(OperationFormItem *opForm);
    OperationFormItem* getOperationAt(int row);
    OperationModel* getConfiguredOps();
    bool isEmpty() const;
    QModelIndex parentItem;

private:
    QList<OperationFormItem*> opFormList;
    OperationModel *operations;
};

#endif // OPERATIONFORMMODEL_H
