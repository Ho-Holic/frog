// self
#include "Tool.h"

void nsRelation::Tool::addToSelection(nsRelation::Entity* newOne) {
  Q_UNUSED(newOne);
}

void nsRelation::Tool::subtractFromSelection(nsRelation::Entity* oldOne) {
  Q_UNUSED(oldOne);
}

void nsRelation::Tool::clearSelection() {
  //
}

void nsRelation::Tool::beginTouch(const QPoint& pos) {
  Q_UNUSED(pos);
  // default implementation do nothing
}

void nsRelation::Tool::move(const QPoint& from, const QPoint& to) {
  Q_UNUSED(from);
  Q_UNUSED(to);
  // default implementation do nothing
}

void nsRelation::Tool::endTouch(const QPoint& pos) {
  Q_UNUSED(pos);
  // default implementation do nothing
}

nsRelation::Tool::~Tool() {
  // this intentionally left blank
}
