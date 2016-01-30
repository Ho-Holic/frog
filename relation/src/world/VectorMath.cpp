#include "VectorMath.h"

QRect nsRelation::VectorMath::fromCenterPoint(const QPoint& center, const QSize& entitySize) {
  QPoint sizeVec = QPoint(entitySize.width(), - entitySize.height());
  QPoint pos = center + (sizeVec / 2) - QPoint(entitySize.width(), 0);
  return QRect(pos, entitySize);
}
