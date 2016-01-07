#ifndef SETTINGSPIDER_PATHPAIR_H
#define SETTINGSPIDER_PATHPAIR_H

// qt
#include <QString>

namespace nsSettingSpider {

  // in case when you need later to pass more information
  class PathPair {
  public:
    PathPair(const QString& path, const QString& name);
    QString path;
    QString name;
  };
}

#endif // PATHPAIR_H
