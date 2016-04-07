// self
#include "HandTool.h"

nsRelation::HandTool::HandTool()
: Tool()
, mOrigin(0, 0) {
  //
}

void nsRelation::HandTool::move(const QPoint& from, const QPoint& to) {
  mOrigin += to - from;
}


