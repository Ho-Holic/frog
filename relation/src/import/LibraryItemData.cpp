// self
#include "LibraryItemData.h"

nsRelation::LibraryItemData::LibraryItemData(const QString& path, const QString& name)
: mPath(path)
, mName(name) {
  //
}

QString nsRelation::LibraryItemData::path() const {
  return mPath;
}

QString nsRelation::LibraryItemData::name() const {
  return mName;
}
