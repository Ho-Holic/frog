#ifndef FROG_RELATION_LIBRARYITEMDATA_H
#define FROG_RELATION_LIBRARYITEMDATA_H

// qt
#include <QString>

namespace nsRelation {

  // in case when you need later to pass more information  
  class LibraryItemData {
  public:
    LibraryItemData(const QString& path, const QString& name);
    QString path() const;
    QString name() const;
  private:
    QString mPath;
    QString mName;
  };
}

#endif // FROG_RELATION_LIBRARYITEMDATA_H
