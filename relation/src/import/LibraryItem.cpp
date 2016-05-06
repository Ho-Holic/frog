// self
#include "LibraryItem.h"

// qt
#include <QtAlgorithms>
#include <QDir>

// tmp
#include <QDebug>

nsRelation::LibraryItem::LibraryItem(Type type,
                                          const LibraryItemData& itemData,
                                          LibraryItem* parentItem)
: mItemType(type)
, mItemData(itemData)
, mParentItem(parentItem)
, mChildItems() {
  //
}

nsRelation::LibraryItem::LibraryItem(Type type,
                                          const QString& name,
                                          LibraryItem* parentItem)
: mItemType(type)
, mItemData(QString(), name)
, mParentItem(parentItem)
, mChildItems() {
  //
}

nsRelation::LibraryItem::~LibraryItem() {
  qDeleteAll(mChildItems);
  mChildItems.clear();
}

void nsRelation::LibraryItem::prependChild(nsRelation::LibraryItem* child) {
  mChildItems.prepend(child);
}

void nsRelation::LibraryItem::appendChild(LibraryItem* child) {
  mChildItems.append(child);  
}

nsRelation::LibraryItem* nsRelation::LibraryItem::parentItem() const {
  return mParentItem;
}

int nsRelation::LibraryItem::row() const {

  return mParentItem ? mParentItem->mChildItems.indexOf(const_cast<LibraryItem*>(this))
                     : 0;
}

int nsRelation::LibraryItem::columnCount() const {
  return 1;
}

int nsRelation::LibraryItem::childCount() const {
  return mChildItems.count();
}

nsRelation::LibraryItem* nsRelation::LibraryItem::childItem(int row) const {
  return mChildItems.value(row);
}

QVariant nsRelation::LibraryItem::data(int column) const {
  Q_UNUSED(column);
  if (mItemType == LibPack && mItemData.name().isEmpty()) {
    return QObject::tr("[ no folder ]");
  }
  if (mItemType == Directory || mItemType == File) {
    return QDir(mItemData.name()).dirName();
  }
  return mItemData.name();
}

bool nsRelation::LibraryItem::isRootItem() const {
  return mParentItem == nullptr;
}

QString nsRelation::LibraryItem::path() const {
  return mItemData.path();
}

QString nsRelation::LibraryItem::name() const {
  return mItemData.name();
}

nsRelation::LibraryItem::Type nsRelation::LibraryItem::type() const {
  return mItemType;
}
