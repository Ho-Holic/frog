// self
#include "LibraryItem.h"

// qt
#include <QtAlgorithms>

// tmp
#include <QDebug>

nsSettingSpider::LibraryItem::LibraryItem(Type type,
                                          const LibraryItemData& itemData,
                                          LibraryItem* parentItem)
: mItemType(type)
, mItemData(itemData)
, mParentItem(parentItem)
, mChildItems() {
  //
}

nsSettingSpider::LibraryItem::LibraryItem(Type type,
                                          const QString& name,
                                          LibraryItem* parentItem)
: mItemType(type)
, mItemData(QString(), name)
, mParentItem(parentItem)
, mChildItems() {
  //
}

nsSettingSpider::LibraryItem::~LibraryItem() {
  qDeleteAll(mChildItems);
}

void nsSettingSpider::LibraryItem::appendChild(LibraryItem* child) {
  mChildItems.append(child);  
}

nsSettingSpider::LibraryItem* nsSettingSpider::LibraryItem::parentItem() const {
  return mParentItem;
}

int nsSettingSpider::LibraryItem::row() const {

  return mParentItem ? mParentItem->mChildItems.indexOf(const_cast<LibraryItem*>(this))
                     : 0;
}

int nsSettingSpider::LibraryItem::columnCount() const {
  return 1;
}

int nsSettingSpider::LibraryItem::childCount() const {
  return mChildItems.count();
}

nsSettingSpider::LibraryItem* nsSettingSpider::LibraryItem::childItem(int row) const {
  return mChildItems.value(row);
}

QVariant nsSettingSpider::LibraryItem::data(int column) const {
  Q_UNUSED(column);
  return mItemData.name();
}

bool nsSettingSpider::LibraryItem::isRootItem() const {
  return mParentItem == nullptr;
}

QString nsSettingSpider::LibraryItem::path() const {
  return mItemData.path();
}

QString nsSettingSpider::LibraryItem::name() const {
  return mItemData.name();
}
