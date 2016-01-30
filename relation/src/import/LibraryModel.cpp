// self
#include "LibraryModel.h"
#include "LibraryItem.h"
#include "LibraryItemData.h"

// qt
#include <QDirIterator>
#include <QMimeData>
#include <QTextStream>

// common
#include "cplusplus11.h"

// tmp
#include <QDebug>

// TODO: two subtrees "active" and "pending"

nsRelation::LibraryModel::LibraryModel(QObject* parent)
: QAbstractItemModel(parent)
, mRootItem(new LibraryItem(LibraryItem::Header, tr("Libraries")))
, mSceneItem(new LibraryItem(LibraryItem::Scene, tr("Scene"), mRootItem))
, mPendingItem(new LibraryItem(LibraryItem::Pending, tr("Pending"), mRootItem)) {
  mRootItem->appendChild(mSceneItem);
  mRootItem->appendChild(mPendingItem);
}

nsRelation::LibraryModel::~LibraryModel() {
  delete mRootItem;
}

void nsRelation::LibraryModel::addPath(const LibraryItemData& itemData) {

  beginInsertRows(QModelIndex(), mRootItem->childCount(), mRootItem->childCount());

  LibraryItem* currentNode = new LibraryItem(LibraryItem::LibPack, itemData, mPendingItem);
  attachFullTreeTo(currentNode);
  mPendingItem->prependChild(currentNode);

  endInsertRows();
}

void nsRelation::LibraryModel::attachFullTreeTo(nsRelation::LibraryItem* parent) const {

  QList<LibraryItem*> parents;
  parents.push_back(parent);

  while ( ! parents.empty()) {

    LibraryItem* currentParent = parents.last();

    attachDirectoriesTo(parents, currentParent);
    attachFilesTo(currentParent);

    // remove parent that was traversed
    parents.pop_back();
  }
}

void nsRelation::LibraryModel::attachDirectoriesTo(QList<LibraryItem*>& parents,
                                                        nsRelation::LibraryItem* parent) const {

  QDir::Filters filter = QDir::Dirs | QDir::NoDotAndDotDot | QDir::Drives | QDir::AllDirs;
  QDirIterator it(parent->path(), filter, QDirIterator::NoIteratorFlags);

  while (it.hasNext()) {
    it.next();

    QString name = parent->name().isEmpty() ? it.fileName()
                                            : parent->name() + "/" + it.fileName();
    LibraryItem* child = new LibraryItem(LibraryItem::Directory,
                                        LibraryItemData(it.filePath(), name),
                                        parent);
    parent->appendChild(child);
    parents.push_front(child);
  }
}

void nsRelation::LibraryModel::attachFilesTo(nsRelation::LibraryItem* parent) const {
  QDir::Filters filter = QDir::NoDotAndDotDot | QDir::Files;
  QDirIterator it(parent->path(), filter, QDirIterator::NoIteratorFlags);

  while (it.hasNext()) {
    it.next();

    QString name = parent->name().isEmpty() ? it.fileName()
                                            : parent->name() + "/" + it.fileName();
    LibraryItem* child = new LibraryItem(LibraryItem::File,
                                        LibraryItemData(it.filePath(), name),
                                        parent);
    parent->appendChild(child);

  }
}

int nsRelation::LibraryModel::columnCount(const QModelIndex& parent) const {

  return parent.isValid() ? static_cast<LibraryItem*>(parent.internalPointer())->columnCount()
                          : mRootItem->columnCount();
}

QVariant nsRelation::LibraryModel::data(const QModelIndex& index, int role) const {

  if ( ! index.isValid()) {
    return QVariant();
  }

  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  LibraryItem* item = static_cast<LibraryItem*>(index.internalPointer());  

  return item->data(index.column());
}

Qt::ItemFlags nsRelation::LibraryModel::flags(const QModelIndex& index) const {

  Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

  return index.isValid() ? Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags
                         : Qt::ItemIsDropEnabled | defaultFlags;

}

QMimeData* nsRelation::LibraryModel::mimeData(const QModelIndexList& indexes) const {

  QMimeData* mimeData = new QMimeData();

  QString data;
  QTextStream stream(&data, QIODevice::WriteOnly);

  foreach (const QModelIndex& index, indexes) {

    if (index.isValid()) {

      LibraryItem* item = static_cast<LibraryItem*>(index.internalPointer());

      if (item->type() == LibraryItem::File) {
        stream << item->name() << ";";
      }
    }
  }

  mimeData->setText(data);
  return mimeData;
}

QVariant nsRelation::LibraryModel::headerData(int section, Qt::Orientation orientation, int role) const {

  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return mRootItem->data(section);
  }

  return QVariant();
}

QModelIndex nsRelation::LibraryModel::index(int row, int column, const QModelIndex& parent) const {

  if ( ! hasIndex(row, column, parent)) {
    return QModelIndex();
  }

  LibraryItem* parentItem = parent.isValid() ? static_cast<LibraryItem*>(parent.internalPointer())
                                             : mRootItem;

  LibraryItem* childItem = parentItem->childItem(row);  

  return childItem ? createIndex(row, column, childItem)
                   : QModelIndex();
}

QModelIndex nsRelation::LibraryModel::parent(const QModelIndex& index) const {

  if ( ! index.isValid()) {
    return QModelIndex();
  }

  LibraryItem* childItem = static_cast<LibraryItem*>(index.internalPointer());
  LibraryItem* parentItem = childItem->parentItem();

  if (parentItem == mRootItem) {
    return QModelIndex();
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int nsRelation::LibraryModel::rowCount(const QModelIndex& parent) const {

  if (parent.column() > 0) {
    return 0;
  }

  LibraryItem* parentItem = parent.isValid() ? static_cast<LibraryItem*>(parent.internalPointer())
                                             : mRootItem;
  return parentItem->childCount();
}
