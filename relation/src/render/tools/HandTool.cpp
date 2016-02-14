// self
#include "HandTool.h"

nsRelation::HandTool::HandTool()
: Tool() {
  //
}

void nsRelation::HandTool::move(const QPoint& from, const QPoint& to) {
  mOrigin += to - from;
}


