#ifndef FROG_RELATION_VECTORMATH_HPP
#define FROG_RELATION_VECTORMATH_HPP

// qt
#include <QRect>

namespace nsRelation {

  class VectorMath {
  public:
    static QRect fromCenterPoint(const QPoint& center, const QSize& entitySize);
  };

}

#endif // FROG_RELATION_VECTORMATH_HPP
