// self
#include "Tools.h"

// tmp
#include <QDebug>

// common
#include "cplusplus11.h"

nsRelation::Tools::Tools(QObject* parent)
: QObject(parent)
, mTools(ToolTypeSize, nullptr)
, mCurrentTool(HandType) {
  mTools[HandType]    = new HandTool(this);
  mTools[MoveType]    = new MoveTool(this);
  mTools[ConnectType] = new ConnectTool(this);

  connect(handTool(),    SIGNAL(onMarkingMenuChanged(const QString&, MarkingMenuItem*)),
          this,          SIGNAL(onMarkingMenuChanged(const QString&, MarkingMenuItem*)));
  connect(moveTool(),    SIGNAL(onMarkingMenuChanged(const QString&, MarkingMenuItem*)),
          this,          SIGNAL(onMarkingMenuChanged(const QString&, MarkingMenuItem*)));
  connect(connectTool(), SIGNAL(onMarkingMenuChanged(const QString&, MarkingMenuItem*)),
          this,          SIGNAL(onMarkingMenuChanged(const QString&, MarkingMenuItem*)));


  connect(handTool(),    SIGNAL(onMarkingMenuSelectionChange(const QPoint&, const QPoint&)),
          this,          SIGNAL(onMarkingMenuSelectionChange(const QPoint&, const QPoint&)));
  connect(moveTool(),    SIGNAL(onMarkingMenuSelectionChange(const QPoint&, const QPoint&)),
          this,          SIGNAL(onMarkingMenuSelectionChange(const QPoint&, const QPoint&)));
  connect(connectTool(), SIGNAL(onMarkingMenuSelectionChange(const QPoint&, const QPoint&)),
          this,          SIGNAL(onMarkingMenuSelectionChange(const QPoint&, const QPoint&)));

}

void nsRelation::Tools::reportMenuStatus(const QString& replyId) {
  this->currentTool()->reportMenuStatus(replyId);
}

nsRelation::HandTool* nsRelation::Tools::handTool() const {

  Q_ASSERT(dynamic_cast<HandTool*>(mTools[HandType]) != nullptr);

  return static_cast<HandTool*>(mTools[HandType]);
}

nsRelation::ConnectTool* nsRelation::Tools::connectTool() const {

  Q_ASSERT(dynamic_cast<ConnectTool*>(mTools[ConnectType]) != nullptr);

  return static_cast<ConnectTool*>(mTools[ConnectType]);
}

nsRelation::MoveTool* nsRelation::Tools::moveTool() const {

  Q_ASSERT(dynamic_cast<MoveTool*>(mTools[MoveType]) != nullptr);

  return static_cast<MoveTool*>(mTools[MoveType]);
}

QPoint nsRelation::Tools::origin() const {
  return handTool()->origin();
}

void nsRelation::Tools::beginTouch(const QPoint& pos) {  
  currentTool()->beginTouch(pos);
}

void nsRelation::Tools::move(const QPoint& from, const QPoint& to) {
  currentTool()->move(from, to);
}

void nsRelation::Tools::endTouch(const QPoint& pos) {
  currentTool()->endTouch(pos);
}

void nsRelation::Tools::reset() {
  currentTool()->reset();
  changeToolTo(HandType);
}

nsRelation::Tool* nsRelation::Tools::currentTool() const {
  return mTools.at(mCurrentTool);
}

nsRelation::ToolType nsRelation::Tools::currentToolType() const {
  return mCurrentTool;
}

void nsRelation::Tools::changeToolTo(nsRelation::ToolType tool) {
  // don't reset tool here, it would break "mouse events chain" invariant
  // you need to reset tool only after onMouseRelease
  mCurrentTool = tool;
}

