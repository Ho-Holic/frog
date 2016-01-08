#ifndef SETTINGSPIDER_VECTORMATH_HPP
#define SETTINGSPIDER_VECTORMATH_HPP

// qt
#include <QRect>

namespace nsSettingSpider {

  class VectorMath {
  public:
    static QRect fromCenterPoint(const QPoint& center, const QSize& entitySize);
  };

}

#endif // SETTINGSPIDER_VECTORMATH_HPP
