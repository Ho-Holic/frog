// self
#include "Tool.h"

nsRelation::Tool::Tool(QObject* parent)
: QObject(parent)
, mOrigin(0, 0)
, mSelectedEntities()
, mMarkingMenu() {
  //
}

nsRelation::Tool::~Tool() {
  qDeleteAll(mMarkingMenu.begin(), mMarkingMenu.end());
}

const QPoint& nsRelation::Tool::origin() const {
  return mOrigin;
}

void nsRelation::Tool::setOrigin(const QPoint& pos) {
  mOrigin = pos;
}


const nsRelation::Tool::SelectionList& nsRelation::Tool::selection() const {
  return mSelectedEntities;
}

void nsRelation::Tool::addToSelection(nsRelation::Entity* selected) {
  mSelectedEntities.push_back(selected);
}

void nsRelation::Tool::clearSelection() {
  mSelectedEntities.clear();
}

void nsRelation::Tool::addToMarkingMenu(const QString& action) {
  MarkingMenuItem* item = new MarkingMenuItem(action);
  mMarkingMenu.push_back(item);
}

void nsRelation::Tool::reportMenuStatus(const QString& replyId) {  

  foreach (MarkingMenuItem* item, mMarkingMenu) {
    emit onMarkingMenuChanged(replyId, item);
  }
}

void nsRelation::Tool::beginTouch(const QPoint& pos) {
  Q_UNUSED(pos);
  // default implementation do nothing

  // TODO: foreach markingmenu set position 360/angle
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


