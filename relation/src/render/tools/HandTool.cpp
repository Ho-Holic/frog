// self
#include "HandTool.h"

nsRelation::HandTool::HandTool(QObject* parent)
: Tool(parent)
, mOrigin(0, 0) {
  //
}

void nsRelation::HandTool::move(const QPoint& from, const QPoint& to) {
  mOrigin += to - from;
}


