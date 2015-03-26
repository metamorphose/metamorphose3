#ifndef DIRMODEL
#define DIRMODEL
#include <QtCore/QAbstractTableModel>
#include "renameritem.h"

class RenamerModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    ~RenamerModel();

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
    int addDirectories(const QStringList &directoryList,
                        const bool &recursive,
                        const QStringList nameFilters,
                        const bool &files,
                        const bool &folders,
                        const bool &hidden);
    int addFiles(const QStringList &fileList);
    bool isEmpty() const;
    bool applyRenamingOps();
    bool renameItems();
    void clear();

signals:
    void operationCompleted(QString message);

protected:
    QModelIndex parentItem;
    void addFile(const QFileInfo &fileInfo);
    int addDirectory(const QString &path,
                      const bool recursive,
                      const QStringList &nameFilters,
                      const QDir::Filters &filter);


private:
    QList<RenamerItem*> itemsList;
    QLocale locale;
};

#endif // DIRMODEL

