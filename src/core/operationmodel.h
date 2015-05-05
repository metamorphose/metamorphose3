#ifndef OPERATIONMODEL_H
#define OPERATIONMODEL_H

#include <QtCore/QAbstractTableModel>
#include "operationitem.h"

class OperationModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OperationModel(QObject *parent = 0);
    ~OperationModel();

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void addOperation(OperationItem *operation);
    std::pair<QString, QString> applyOperations(const int &index, std::pair<QString, QString> oldName);
    void clear();
    bool isEmpty() const;

protected:
    QModelIndex parentItem;

private:
    QList<OperationItem*> itemsList;
};

#endif // OPERATIONMODEL_H
