#ifndef SETTINGSPIDER_LIBRARYITEM_H
#define SETTINGSPIDER_LIBRARYITEM_H

// qt
#include <QVariant>

namespace nsSettingSpider {

  class PathPair;

  class LibraryItem {
  public:
    // for invisible root case
    LibraryItem();
    LibraryItem(const PathPair& pathPair, LibraryItem* parentItem);
    ~LibraryItem();
  public:
    void appendChild(LibraryItem* child);
    LibraryItem* childItem(int row);
    LibraryItem* parentItem();
    int row();
    int columnCount();
    int childCount();
    QVariant data(int column);
  private:
    QString mPath;
    QString mName;
    LibraryItem* mParentItem;
    QList<LibraryItem*> mChildItems;
  };

}

#endif // SETTINGSPIDER_LIBRARYITEM_H
