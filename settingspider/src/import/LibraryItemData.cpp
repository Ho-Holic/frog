// self
#include "LibraryItemData.h"

nsSettingSpider::LibraryItemData::LibraryItemData(const QString& path, const QString& name)
: mPath(path)
, mName(name) {
  //
}

QString nsSettingSpider::LibraryItemData::path() const {
  return mPath;
}

QString nsSettingSpider::LibraryItemData::name() const {
  return mName;
}
