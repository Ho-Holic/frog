#ifndef FROG_RELATION_HANDTOOL_HPP
#define FROG_RELATION_HANDTOOL_HPP

// self
#include "Tool.h"

namespace nsRelation {

  class HandTool : public Tool {
  public:
    HandTool();
  public:
    virtual void beginTouch(const QPoint& pos);
    virtual void move(const QPoint& from, const QPoint& to);
    virtual void endTouch(const QPoint& pos);
  };
}

#endif // FROG_RELATION_HANDTOOL_HPP
