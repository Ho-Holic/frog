#ifndef SETTINGSPIDER_LIBRARYMODEL_H
#define SETTINGSPIDER_LIBRARYMODEL_H

// qt
#include <QAbstractItemModel>

class QMimeData;

namespace nsSettingSpider {

  class LibraryItem;
  class LibraryItemData;

  class LibraryModel : public QAbstractItemModel {
    Q_OBJECT
  public:
    LibraryModel(QObject* parent = 0);
    ~LibraryModel();
  public slots:
    void addPath(const LibraryItemData& itemData);
  public:
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex & index) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const;
    virtual QMimeData* mimeData(const QModelIndexList& indexes) const;
  private:
    void attachFullTreeTo(LibraryItem* parent) const;
    void attachDirectoriesTo(QList<LibraryItem*>& parents, LibraryItem* parent) const;
    void attachFilesTo(LibraryItem* parent) const;
  private:
    LibraryItem* mRootItem;
    LibraryItem* mSceneItem;
    LibraryItem* mPendingItem;
  };
}

#endif // SETTINGSPIDER_LIBRARYMODEL_H
