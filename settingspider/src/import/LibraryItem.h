#ifndef SETTINGSPIDER_LIBRARYITEM_H
#define SETTINGSPIDER_LIBRARYITEM_H

// self
#include "LibraryItemData.h"

// common
#include "cplusplus11.h"

// qt
#include <QVariant>

namespace nsSettingSpider {  

  class LibraryItem {
  public:
    enum Type {
      Header,
      Pending,
      Scene,
      LibPack,
      Directory,
      File
    };
  public:    
    LibraryItem(Type type,
                const QString& name,
                LibraryItem* parentItem = nullptr);
    LibraryItem(Type type,
                const LibraryItemData& itemData,
                LibraryItem* parentItem);
    ~LibraryItem();
  public:
    void prependChild(LibraryItem* child);
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
    Type type() const;
  private:
    Type mItemType;
    LibraryItemData mItemData;
    LibraryItem* mParentItem;
    QList<LibraryItem*> mChildItems;    
  };

}

#endif // SETTINGSPIDER_LIBRARYITEM_H
