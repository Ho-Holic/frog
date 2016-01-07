#ifndef SETTINGSPIDER_LIBRARYITEM_H
#define SETTINGSPIDER_LIBRARYITEM_H

// qt
#include <QVariant>

namespace nsSettingSpider {

  class LibraryItemData;

  class LibraryItem {
  public:    
    LibraryItem();
    LibraryItem(const LibraryItemData& pathPair, LibraryItem* parentItem);
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
  private:
    QString mPath;
    QString mName;
    LibraryItem* mParentItem;
    QList<LibraryItem*> mChildItems;    
  };

}

#endif // SETTINGSPIDER_LIBRARYITEM_H
