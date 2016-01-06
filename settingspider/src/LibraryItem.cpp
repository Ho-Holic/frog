// self
#include "LibraryItem.h"
#include "PathPair.h"

// common
#include "cplusplus11.h"

// qt
#include <QtAlgorithms>

nsSettingSpider::LibraryItem::LibraryItem(const PathPair& pathPair, LibraryItem* parentItem)
: mPath(pathPair.path)
, mName(pathPair.name)
, mParentItem(parentItem)
, mChildItems() {
  //
}

nsSettingSpider::LibraryItem::LibraryItem()
: mPath()
, mName()
, mParentItem(nullptr)
, mChildItems() {
  //
}

nsSettingSpider::LibraryItem::~LibraryItem() {
  qDeleteAll(mChildItems);
}

void nsSettingSpider::LibraryItem::appendChild(LibraryItem* child) {
  mChildItems.append(child);
}

nsSettingSpider::LibraryItem*nsSettingSpider::LibraryItem::parentItem() {
  return mParentItem;
}

int nsSettingSpider::LibraryItem::row() {

  return mParentItem ? mParentItem->mChildItems.indexOf(const_cast<LibraryItem*>(this))
                     : 0;
}

int nsSettingSpider::LibraryItem::columnCount() {
  return 1;
}

int nsSettingSpider::LibraryItem::childCount() {
  return mChildItems.count();
}

nsSettingSpider::LibraryItem* nsSettingSpider::LibraryItem::childItem(int row) {
  return mChildItems.value(row);
}

QVariant nsSettingSpider::LibraryItem::data(int column) {
  return "cat on mars";
}
