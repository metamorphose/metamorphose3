#ifndef OPERATIONMODEL_H
#define OPERATIONMODEL_H
#include <QtCore/QAbstractTableModel>


class OperationModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    ~OperationModel();

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    void addOperation(QObject *operation);

protected:
    QModelIndex parentItem;

private:
    QList<QObject*> itemsList;
};

#endif // OPERATIONMODEL_H
