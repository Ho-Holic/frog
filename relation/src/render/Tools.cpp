// self
#include "Tools.h"

// tools
#include "tools/ConnectTool.h"
#include "tools/HandTool.h"
#include "tools/MoveTool.h"

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
