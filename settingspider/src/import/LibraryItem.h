#ifndef SETTINGSPIDER_LIBRARYITEM_H
#define SETTINGSPIDER_LIBRARYITEM_H

// self
#include "LibraryItemData.h"

// qt
#include <QVariant>

namespace nsSettingSpider {  

  class LibraryItem {
  public:
    enum Type { Root, Directory, File };
  public:    
    LibraryItem();
    LibraryItem(Type type,
                const LibraryItemData& itemData,
                LibraryItem* parentItem);
    ~LibraryItem();
  public:
    void appendChild(LibraryItem* child);
    LibraryItem* childItem(int row) const;
    LibraryItem* parentItem() const;
    int row() const;
    int columnCount() const;
    int childCount() const;
    QVariant data(int column) const;
    bool isRootItem() const;
    QString path() const;
    QString name() const;
  private:
    Type mItemType;
    LibraryItemData mItemData;
    LibraryItem* mParentItem;
    QList<LibraryItem*> mChildItems;    
  };

}

#endif // SETTINGSPIDER_LIBRARYITEM_H
