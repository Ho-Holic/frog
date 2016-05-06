// self
#include "Tool.h"

nsRelation::Tool::Tool(QObject* parent)
: QObject(parent)
, mOrigin(0, 0)
, mSelectedEntities()
, mMarkingMenu()
, mIsMarkingMenuOpened(false)
, mMarkingMenuPosition(0, 0)
, mCursorPosition(0, 0) {
  //
}

nsRelation::Tool::~Tool() {
  qDeleteAll(mMarkingMenu.begin(), mMarkingMenu.end());
  mMarkingMenu.clear();
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

  if ( ! isMarkingMenuOpened()) return;

  foreach (MarkingMenuItem* item, mMarkingMenu) {
    emit onMarkingMenuChanged(replyId, item);
  }
}

void nsRelation::Tool::popMarkingMenu(const QPoint& pos) {
  mMarkingMenuPosition = pos;
  mIsMarkingMenuOpened = true;

  //double angleStep = 360.0 / mMarkingMenu.size();
  QPoint oldPos = mMarkingMenuPosition;
  QPoint offsetBetweenButtons(10, 0);

  foreach (MarkingMenuItem* item, mMarkingMenu) {
    item->moveTopLeft(oldPos);
    oldPos = item->rect().topRight() + offsetBetweenButtons;
  }
}

bool nsRelation::Tool::isMarkingMenuOpened() const {
  return mIsMarkingMenuOpened;
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
  mIsMarkingMenuOpened = false;
  mMarkingMenuPosition = QPoint(0,0);
}


