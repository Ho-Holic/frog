// self
#include "LibraryModel.h"
#include "LibraryItem.h"
#include "PathPair.h"

// common
#include "cplusplus11.h"

nsSettingSpider::LibraryModel::LibraryModel(QObject* parent)
: QAbstractItemModel(parent)
, mInvisibleRoot(new LibraryItem(PathPair("a", "b"), nullptr)) {
  //
}

nsSettingSpider::LibraryModel::~LibraryModel() {
  delete mInvisibleRoot;
}

void nsSettingSpider::LibraryModel::addPath(const PathPair& pathPair) {
  LibraryItem* child = new LibraryItem(pathPair, mInvisibleRoot);
  mInvisibleRoot->appendChild(child);
}

int nsSettingSpider::LibraryModel::columnCount(const QModelIndex& parent) const {

  return parent.isValid() ? static_cast<LibraryItem*>(parent.internalPointer())->columnCount()
                          : mInvisibleRoot->columnCount();
}

QVariant nsSettingSpider::LibraryModel::data(const QModelIndex& index, int role) const {

  if ( ! index.isValid()) {
    return QVariant();
  }

  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  LibraryItem* item = static_cast<LibraryItem*>(index.internalPointer());

  return item->data(index.column());
}

Qt::ItemFlags nsSettingSpider::LibraryModel::flags(const QModelIndex& index) const {
  if ( ! index.isValid()) {
    return 0;
  }

  return QAbstractItemModel::flags(index);
}

QVariant nsSettingSpider::LibraryModel::headerData(int section, Qt::Orientation orientation, int role) const {

  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return mInvisibleRoot->data(section);
  }

  return QVariant();
}

QModelIndex nsSettingSpider::LibraryModel::index(int row, int column, const QModelIndex& parent) const {

  if ( ! hasIndex(row, column, parent)) {
    return QModelIndex();
  }

  LibraryItem* parentItem = parent.isValid() ? static_cast<LibraryItem*>(parent.internalPointer())
                                             : mInvisibleRoot;

  LibraryItem* childItem = parentItem->childItem(row);

  return childItem ? createIndex(row, column, childItem)
                   : QModelIndex();
}

QModelIndex nsSettingSpider::LibraryModel::parent(const QModelIndex& index) const {

  if ( ! index.isValid()) {
    return QModelIndex();
  }

  LibraryItem* childItem = static_cast<LibraryItem*>(index.internalPointer());
  LibraryItem* parentItem = childItem->parentItem();

  if (parentItem == mInvisibleRoot) {
    return QModelIndex();
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int nsSettingSpider::LibraryModel::rowCount(const QModelIndex& parent) const {

  if (parent.column() > 0) {
    return 0;
  }

  LibraryItem* parentItem = parent.isValid() ? static_cast<LibraryItem*>(parent.internalPointer())
                                             : mInvisibleRoot;
  return parentItem->childCount();
}
