#ifndef DIRMODEL
#define DIRMODEL
#include <QtCore/QAbstractTableModel>
#include "diritem.h"

class DirModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DirModel(QObject *parent = 0);
    ~DirModel();

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) Q_DECL_OVERRIDE;
    void addDirectories(const QStringList &directoryList,
                        const bool &recursive,
                        const QStringList nameFilters,
                        const bool &files,
                        const bool &folders,
                        const bool &hidden);
    void addFiles(const QStringList &fileList);
    bool applyRenamingRules();
    bool renameItems();
    void clear();

signals:
    void operationCompleted(QString message);

protected:
    QModelIndex parentItem;
    void addFile(const QFileInfo &fileInfo);
    bool addDirectory(const QString &path,
                      const bool recursive,
                      const QStringList &nameFilters,
                      const QDir::Filters &filter);


private:
    QList<DirItem*> dirItems;
    QLocale locale;
};

#endif // DIRMODEL

