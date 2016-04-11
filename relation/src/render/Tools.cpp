// self
#include "Tools.h"

// tmp
#include <QDebug>

nsRelation::Tools::Tools()
: mTools(ToolTypeSize, nullptr)
, mCurrentTool(HandTool)
, mIsLocked(false) {
  mTools[HandType]    = new HandTool();
  mTools[MoveType]    = new MoveTool();
  mTools[ConnectType] = new ConnectTool();
}

nsRelation::Tools::~Tools() {
  qDeleteAll(mTools);
}

nsRelation::HandTool* nsRelation::Tools::handTool() const {

  Q_ASSERT(dynamic_cast<HandTool*>(mTools[HandType]) != nullptr);

  return static_cast<HandTool*>(mTools[HandType]);
}

nsRelation::ConnectTool *nsRelation::Tools::connectTool() const {

  Q_ASSERT(dynamic_cast<ConnectTool*>(mTools[ConnectType]) != nullptr);

  return static_cast<ConnectTool*>(mTools[ConnectType]);
}

QPoint nsRelation::Tools::origin() const {
  return handTool()->origin();
}

void nsRelation::Tools::beginTouch(const QPoint& pos) {
  mIsLocked = true;
  currentTool()->beginTouch(pos);
}

void nsRelation::Tools::move(const QPoint& from, const QPoint& to) {
  currentTool()->move(from, to);
}

void nsRelation::Tools::endTouch(const QPoint& pos) {
  currentTool()->endTouch(pos);
  mIsLocked = false;
}

nsRelation::Tool* nsRelation::Tools::currentTool() const {
  return mTools.at(mCurrentTool);
}

nsRelation::Tools::ToolType nsRelation::Tools::currentToolType() const {
  return mCurrentTool;
}

void nsRelation::Tools::changeToolTo(nsRelation::Tools::ToolType tool) {
  if ( ! isLocked()) {
    mCurrentTool = tool;
  }
  else {
    qDebug() << "attempt to change locked tool";
  }
}

bool nsRelation::Tools::isLocked() const {
  return mIsLocked;
}
