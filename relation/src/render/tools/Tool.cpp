// self
#include "Tool.h"

nsRelation::Tool::Tool(QObject* parent)
: QObject(parent)
, mSelectedEntities() {
  //
}

nsRelation::Tool::~Tool() {
  // this intentionally left blank
}

const nsRelation::Tool::SelectionList& nsRelation::Tool::selection() const {
  return mSelectedEntities;
}

void nsRelation::Tool::addToSelection(nsRelation::Entity* selected) {
  mSelectedEntities.push_back(selected);
}

void nsRelation::Tool::subtractFromSelection(nsRelation::Entity* oldOne) {
  Q_UNUSED(oldOne);
}

void nsRelation::Tool::clearSelection() {
  mSelectedEntities.clear();
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

void nsRelation::Tool::reset() {
  clearSelection();
}


