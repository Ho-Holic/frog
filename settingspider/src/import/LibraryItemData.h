#ifndef SETTINGSPIDER_LIBRARYITEMDATA_H
#define SETTINGSPIDER_LIBRARYITEMDATA_H

// qt
#include <QString>

namespace nsSettingSpider {

  // in case when you need later to pass more information  
  class LibraryItemData {
  public:
    LibraryItemData(const QString& path, const QString& name);
    QString path;
    QString name;
  };
}

#endif // SETTINGSPIDER_LIBRARYITEMDATA_H
