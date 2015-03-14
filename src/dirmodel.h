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

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    bool addDirectory(const QString &path, const bool recursive);
    void addDirectories(const QStringList &directoryList, const bool &recursive);
    void addFiles(const QStringList &fileList);
    void addFile(const QString &file);

public slots:
    bool applyRenamingRules();
    bool renameItems();
    void clear();

protected:
    QModelIndex parentItem;
    void addFile(const QFileInfo &fileInfo);

private:
    QList<DirItem*> dirItems;
    QLocale locale;
};

#endif // DIRMODEL

