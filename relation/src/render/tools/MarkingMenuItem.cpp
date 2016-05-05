// self
#include "MarkingMenuItem.h"
#include "src/render/ColorScheme.h"

nsRelation::MarkingMenuItem::MarkingMenuItem(const QString& actionName)
: mActionName(actionName)
, mRect(QPoint(0, 0), ColorScheme::boxForText(actionName)) {
  //
}

void nsRelation::MarkingMenuItem::moveTopLeft(const QPoint& pos) {
  mRect.moveTopLeft(pos);
}

const QString& nsRelation::MarkingMenuItem::actionName() const {
  return mActionName;
}

const QRect& nsRelation::MarkingMenuItem::rect() const {
  return mRect;
}
