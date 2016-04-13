// self
#include "HandTool.h"

nsRelation::HandTool::HandTool(QObject* parent)
: Tool(parent)
, mOrigin(0, 0) {
  //
}

const QPoint& nsRelation::HandTool::origin() const {
  return mOrigin;
}

void nsRelation::HandTool::move(const QPoint& from, const QPoint& to) {
  mOrigin += to - from;
}


