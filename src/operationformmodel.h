#ifndef OPERATIONFORMMODEL_H
#define OPERATIONFORMMODEL_H

#include <QtWidgets/QWidget>
#include <QtCore/QAbstractTableModel>
#include "operationformitem.h"


class OperationFormModel : public QAbstractTableModel
{
public:
    explicit OperationFormModel(QObject *parent = 0);
    ~OperationFormModel();

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    void addOperation(OperationFormItem *operation);

protected:
    QModelIndex parentItem;

private:
    QList<OperationFormItem*> m_operations;
};

#endif // OPERATIONFORMMODEL_H
