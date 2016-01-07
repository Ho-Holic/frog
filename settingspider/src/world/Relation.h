#ifndef SETTINGSPIDER_RELATION_H
#define SETTINGSPIDER_RELATION_H

// qt
#include <QString>

namespace nsSettingSpider {

  typedef QString RelationType;

  class Relation {
  public:
    static QString Needed;
    static QString Absorb;
  };
}

#endif // SETTINGSPIDER_RELATION_H
