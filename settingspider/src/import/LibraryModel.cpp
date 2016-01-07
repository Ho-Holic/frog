// self
#include "LibraryModel.h"
#include "LibraryItem.h"
#include "LibraryItemData.h"

// qt
#include <QDirIterator>

// common
#include "cplusplus11.h"

// tmp
#include <QDebug>

// TODO: two subtrees "active" and "pending"

nsSettingSpider::LibraryModel::LibraryModel(QObject* parent)
: QAbstractItemModel(parent)
, mRootItem(new LibraryItem()) {
  //  
}

nsSettingSpider::LibraryModel::~LibraryModel() {
  delete mRootItem;
}

void nsSettingSpider::LibraryModel::addPath(const LibraryItemData& itemData) {

  beginInsertRows(QModelIndex(), mRootItem->childCount(), mRootItem->childCount());

  LibraryItem* currentNode = new LibraryItem(LibraryItem::Directory, itemData, mRootItem);
  attachTreeTo(currentNode);

  mRootItem->appendChild(currentNode);

  endInsertRows();
}

void nsSettingSpider::LibraryModel::attachTreeTo(nsSettingSpider::LibraryItem* parent) const {

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

void nsSettingSpider::LibraryModel::attachDirectoriesTo(QList<LibraryItem*>& parents,
                                                        nsSettingSpider::LibraryItem* parent) const {

  QDir::Filters filter = QDir::Dirs | QDir::NoDotAndDotDot | QDir::Drives | QDir::AllDirs;
  QDirIterator it(parent->path(), filter, QDirIterator::NoIteratorFlags);

  while (it.hasNext()) {
    it.next();

    LibraryItem* child = new LibraryItem(LibraryItem::Directory,
                                        LibraryItemData(it.filePath(), it.fileName()),
                                        parent);
    parent->appendChild(child);
    parents.push_front(child);
  }
}

void nsSettingSpider::LibraryModel::attachFilesTo(nsSettingSpider::LibraryItem* parent) const {
  QDir::Filters filter = QDir::NoDotAndDotDot | QDir::Files;
  QDirIterator it(parent->path(), filter, QDirIterator::NoIteratorFlags);

  while (it.hasNext()) {
    it.next();
    LibraryItem* child = new LibraryItem(LibraryItem::File,
                                        LibraryItemData(it.filePath(), it.fileName()),
                                        parent);
    parent->appendChild(child);

  }
}

int nsSettingSpider::LibraryModel::columnCount(const QModelIndex& parent) const {

  return parent.isValid() ? static_cast<LibraryItem*>(parent.internalPointer())->columnCount()
                          : mRootItem->columnCount();
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
    return mRootItem->data(section);
  }

  return QVariant();
}

QModelIndex nsSettingSpider::LibraryModel::index(int row, int column, const QModelIndex& parent) const {

  if ( ! hasIndex(row, column, parent)) {
    return QModelIndex();
  }

  LibraryItem* parentItem = parent.isValid() ? static_cast<LibraryItem*>(parent.internalPointer())
                                             : mRootItem;

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

  if (parentItem == mRootItem) {
    return QModelIndex();
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int nsSettingSpider::LibraryModel::rowCount(const QModelIndex& parent) const {

  if (parent.column() > 0) {
    return 0;
  }

  LibraryItem* parentItem = parent.isValid() ? static_cast<LibraryItem*>(parent.internalPointer())
                                             : mRootItem;
  return parentItem->childCount();
}
